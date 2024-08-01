import json
from http import HTTPStatus

from werkzeug.wrappers import Request

from server.admin_handler import AdminHandler
from server.model_handler import ModelHandler
from server.postgres_model import PostgresModel
from server.response_data import ResponseData
from server.settings import load_settings


class TddAirServer(object):
    def __init__(self, settings):
        self.settings = settings
        self.model = PostgresModel(settings)
        self.admin_handler = AdminHandler(settings, self.model)
        self.model_handler = ModelHandler(settings, self.model)

    def __call__(self, environ, start_response):
        return self.wsgi_app(environ, start_response)

    def wsgi_app(self, environ, start_response):
        request = Request(environ)
        response = self.dispatch_request(request).make_response()
        return response(environ, start_response)

    def dispatch_request(self, request) -> ResponseData:
        print(request.path)
        print(request.method)
        print(request.json)
        if request.json:
            # args = json.loads(request.json)
            args = request.json
        else:
            args = {}
        try:
            match request.path:
                case "/admin/status":
                    return self.admin_handler.status()
                case "/admin/drop_db":
                    return self.admin_handler.drop_db()
                case "/admin/create_db":
                    return self.admin_handler.create_db(
                        delete_if_exists=args.get("delete-if-exists"))
                case "/get-member":
                    return self.model_handler.get_member(args["username"])
                case "/list-members":
                    return self.model_handler.list_members()
                case "/create-member":
                    return self.model_handler.create_member(
                        username=args["username"],
                        name=args["name"],
                        password=args["password"],
                        email=args["email"],
                        data=args.get("data") or {})
                case "/create-flight":
                    return self.model_handler.create_flight(
                        origin=args["origin"],
                        destination=args["destination"],
                        mileage=args["mileage"],
                        airline=args["airline"],
                        number=args["number"])
                case "/get-flight":
                    return self.model_handler.get_flight(
                        airline=args["airline"],
                        number=args["number"])


            return ResponseData(
                status="error",
                code=HTTPStatus.NOT_FOUND,  # 404
                description=f"Unrecognized path: {request.path}")
        except Exception as e:
            print(f"Unexpected exception: {e}")
            return ResponseData(
                status="error",
                code=500,
                description="Unexpected error")



def create_app(settings=None):
    if settings is None:
        settings = load_settings()
    print("[Settings]-----")
    print(settings)
    print("---------------")
    # print(f"API version: {api_version}")

    server_app = TddAirServer(settings)
    return server_app


app = create_app()

# Dev mode
if __name__ == '__main__':
    from werkzeug.serving import run_simple
    app_port = app.settings.flask_run_port
    run_simple('127.0.0.1', app_port, app, use_debugger=True, use_reloader=True)