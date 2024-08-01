from psycopg2 import pool
from pydantic.types import SecretStr


class PooledConnection:
    def __init__(self, connection_pool):
        self.connection = connection_pool.getconn()
        self.pool = connection_pool

        if self.connection is None:
            raise Exception("Too many database connections")

    def return_to_pool(self):
        self.pool.putconn(self.connection)
        self.connection = None


class ConnectionPool:
    def __init__(self, hostname: str, port: int, password: SecretStr, db_name: str):
        self.hostname = hostname
        self.port = port
        self.password = password
        self.db_name = db_name
        self.pool = None

    def get_connection(self):
        if not self.pool:
            self.pool = pool.ThreadedConnectionPool(
                1, 4,
                user="postgres",
                password=self.password.get_secret_value(),
                host=self.hostname,
                port=self.port,
                database=self.db_name
            )

        return PooledConnection(self.pool)

    def close_all(self):
        if self.pool:
            self.pool.closeall()
            self.pool = None
