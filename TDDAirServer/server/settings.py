import os

from dotenv import load_dotenv
from pydantic import SecretStr
from pydantic_settings import BaseSettings


class Settings(BaseSettings):
    db_url: str
    db_name: str
    db_password: SecretStr

    flask_run_port: int = 5001


def load_settings() -> Settings:
    load_dotenv()
    env_file = os.environ.get("ENV_FILE")
    if env_file:
        load_dotenv(env_file, override=True)
    return Settings()
