import requests

server_url = "http://localhost:5001"

class Server:
    def post_request(self, command: str, args):
        return requests.post(f"{server_url}/{command}", json=args).json()
