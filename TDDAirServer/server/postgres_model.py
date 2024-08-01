from datetime import datetime

from urllib.parse import urlparse

from .connection_pool import ConnectionPool, PooledConnection
from psycopg2.extras import Json
from .settings import Settings


class PostgresModel:
    def __init__(self, settings: Settings):
        db_url = urlparse(settings.db_url)
        self.pool = ConnectionPool(
            hostname=db_url.hostname,
            port=db_url.port,
            password=settings.db_password,
            db_name=settings.db_name
        )

    def start_transaction(self):
        return Transaction(self.pool.get_connection())

    def close_all(self):
        self.pool.close_all()


class Transaction:
    def __init__(self, pooled_connection: PooledConnection):
        self.pooled_connection = pooled_connection
        self.needs_committing = False

    @property
    def db(self):
        return self.pooled_connection.connection

    def __enter__(self):
        cursor = self.db.cursor().__enter__()
        self.db.autocommit = False
        return PostgresModelIO(cursor, self)

    def __exit__(self, exc_type, exc_val, exc_tb):
        if self.needs_committing:
            self.db.rollback()
        self.db.cursor().__exit__(exc_type, exc_val, exc_tb)
        self.pooled_connection.return_to_pool()

    def set_needs_update(self):
        self.needs_committing = True

    def commit(self):
        self.db.commit()
        self.needs_committing = False


class ModelIOBase:
    def __init__(self, cursor, trans: Transaction):
        self.cursor = cursor
        self.trans = trans

    def commit(self):
        self.trans.commit()

    def insert_into(self, insert_statement: str, args, returning: str = None):
        self.trans.set_needs_update()
        if returning:
            self.cursor.execute(f"INSERT INTO {insert_statement} RETURNING {returning}", args)
            row = self.cursor.fetchone()
            if row:
                return row[0]
            else:
                return None
        else:
            self.cursor.execute("INSERT INTO " + insert_statement, args)

    def update(self, update_statement: str, args, returning: str = None):
        self.trans.set_needs_update()
        if returning:
            self.cursor.execute(f"UPDATE {update_statement} RETURNING {returning}", args)
            row = self.cursor.fetchone()
            if row:
                return row[0]
            else:
                return None
        else:
            self.cursor.execute("UPDATE " + update_statement, args)

    def delete_from(self, delete_statement: str, args):
        self.trans.set_needs_update()
        self.cursor.execute("DELETE FROM " + delete_statement, args)

    def select_one(self, select_statement: str, args):
        self.cursor.execute("SELECT " + select_statement, args)
        return self.cursor.fetchone()

    def select_value(self, select_statement: str, args):
        self.cursor.execute("SELECT " + select_statement, args)
        return self.cursor.fetchone()[0]

    def select_all(self, select_statement: str, args=None):
        if args:
            self.cursor.execute("SELECT " + select_statement, args)
        else:
            self.cursor.execute("SELECT " + select_statement)
        return self.cursor.fetchall()


class PostgresModelIO(ModelIOBase):

    # Admin features
    def execute_schema(self, schema_sql: str):
        self.trans.set_needs_update()
        self.cursor.execute(schema_sql)

    def get_member(self, username: str) -> dict | None:
        member = self.select_one("password, name, email, data from member where username=%s", (username,))
        if member is None:
            return None
        else:
            return {
                "password": member[0],
                "name": member[1],
                "email": member[2],
                "data": member[3]
            }

    def list_members(self) -> [str]:
        members = self.select_all("username from member")
        if members is None:
            return []
        else:
            return [member[0] for member in members]

    def create_member(self, username: str, name: str, password: str, email: str, data: str):
        self.insert_into("member (username, name, password, email, data) values (%s, %s, %s, %s, %s)",
                         (username, name, password, email, Json(data)))

    def create_flight(self, origin: str, destination: str, mileage: int, airline: str, number: str):
        self.insert_into("flight (origin, destination, mileage, airline, number) values (%s, %s, %s, %s, %s)",
                         (origin, destination, mileage, airline, number))

    def get_flight(self, airline: str, number: str) -> dict | None:
        flight = self.select_one("origin, destination, mileage from flight where airline=%s and number=%s",
                                 (airline, number))
        if flight is None:
            return None
        else:
            return {
                "origin": flight[0],
                "destination": flight[1],
                "mileage": flight[2],
                "airline": airline,
                "number": number
            }