import json
from dataclasses import dataclass
from http import HTTPStatus

from werkzeug import Response

api_version = "0.1"


@dataclass
class ResponseData:
    status: str = "ok"
    code: int = HTTPStatus.OK  # 200
    description: str | None = None
    payload: dict | None = None

    def make_response(self) -> Response:
        assert self.code == HTTPStatus.OK or self.status != "ok"

        data = {
            "status": self.status,
            "code": self.code,
            "api_version": api_version
        }
        if self.description:
            data["description"] = self.description
        if self.payload:
            data = data | self.payload
        return Response(json.dumps(data), status=500, mimetype='application/json')
