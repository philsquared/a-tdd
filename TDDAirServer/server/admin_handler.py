import os
from http import HTTPStatus
from urllib.parse import urlparse

import psycopg2
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT

from server.response_data import ResponseData
from server.settings import Settings


class AdminHandler:

    def __init__(self, settings: Settings, model):
        self.settings = settings
        self.model = model

    def connect_to_db_server(self):
        db_url = urlparse(self.settings.db_url)
        print(f"Connecting to db server: {db_url.hostname}:{db_url.port}")
        self.model.close_all()
        return psycopg2.connect(
            user="postgres",
            password=self.settings.db_password.get_secret_value(),
            host=db_url.hostname,
            port=db_url.port
        )

    def status(self):
        db_found = False
        try:
            db = self.connect_to_db_server()
            connected_to_db_server = True
            db.close()

            try:
                with self.model.start_transaction() as io:
                    db_found = True
            except:
                db_found = False
        except:
            connected_to_db_server = False

        if db_found:
            return ResponseData(
                status="Server is running normally"
            )
        elif connected_to_db_server:
            return ResponseData(
                status="Database does not exist",
                code=HTTPStatus.NO_CONTENT
            )
        else:
            return ResponseData(
                status="Unable to connect to database server",
                code=HTTPStatus.SERVICE_UNAVAILABLE
            )

    def _drop_db(self, db):
        if not db:
            db = self.connect_to_db_server()

        db_name = self.settings.db_name

        print(f"dropping database: {db_name}")
        try:
            db.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)
            with db.cursor() as cursor:
                cursor.execute(f'drop database "{db_name}" WITH (FORCE);')
        except Exception as e:
            db.close()
            raise e
        return db

    def drop_db(self):
        try:
            db = self._drop_db(None)
            db.close()
            return ResponseData(status="Database dropped")
        except Exception as e:
            return ResponseData(
                code=HTTPStatus.INTERNAL_SERVER_ERROR,
                status="Unable to drop database",
                payload={ "exception": str(e) }
            )

    def create_db(self, delete_if_exists: bool):

        self.model.close_all()

        db_name = self.settings.db_name

        db = None
        try:
            db = self.connect_to_db_server()
        except Exception as e:
            if db:
                db.close()
            return ResponseData(
                code=HTTPStatus.INTERNAL_SERVER_ERROR,
                status="Unable to connect to database server",
                payload={"exception": str(e)}
            )

        try:
            with db.cursor() as cursor:
                cursor.execute("SELECT count(datname) FROM pg_catalog.pg_database WHERE datname = %s",
                               (db_name,))
                result = cursor.fetchone()[0]
        except Exception as e:
            db.close()
            return ResponseData(
                code=HTTPStatus.INTERNAL_SERVER_ERROR,
                status="Unable to query database server",
                payload={"exception": str(e)}
            )

        if result > 0:
            if not delete_if_exists:
                db.close()
                return ResponseData(
                    code=HTTPStatus.CONFLICT,
                    status="Unable to create database",
                    description=f"Database '{db_name}' already exists"
                )
            else:
                try:
                    self._drop_db(db)
                except Exception as e:
                    db.close()
                    return ResponseData(
                        code=HTTPStatus.INTERNAL_SERVER_ERROR,
                        status="Unable to drop database",
                        payload={"exception": str(e)}
                    )

        print("Loading schema")
        try:
            this_dir = os.path.dirname(os.path.realpath(__file__))
            schema_file = os.path.join(this_dir, "../schema.sql")
            schema_sql = open(schema_file, "r").read()
        except Exception as e:
            return ResponseData(
                code=HTTPStatus.INTERNAL_SERVER_ERROR,
                status="Error reading schema file",
                payload={"exception": str(e)}
            )

        try:
            print(f"Creating database: {db_name}")
            db.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)
            with db.cursor() as cursor:
                cursor.execute(f'create database "{db_name}";')
        except Exception as e:
            db.close()
            return ResponseData(
                code=HTTPStatus.INTERNAL_SERVER_ERROR,
                status="Unable to create database",
                payload={"exception": str(e)}
            )

        db.close()

        print(f"Connecting to database: {db_name}")
        try:
            with self.model.start_transaction() as tx:
                print("Committing schema")
                tx.execute_schema(schema_sql)
                tx.commit()
        except Exception as e:
            return ResponseData(
                code=HTTPStatus.INTERNAL_SERVER_ERROR,
                status="Unable to execute schema script",
                payload={"exception": str(e)}
            )

        print(f"Database '{db_name}' (re)created and initialised")
        return ResponseData(
            status="Created database",
            description=f"Created database {db_name}"
        )
