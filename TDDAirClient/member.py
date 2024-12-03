from http import HTTPStatus

from server import Server


class Member:
    def __init__(self, server: Server, username: str, name=None, password=None, email=None):
        if name:
            args = {
                "username": username,
                "name": name,
                "password": password,
                "email": email
            }
            response = server.post_request("create-member", args)
            self.isvalid = (response["code"] == HTTPStatus.OK)
            self.username = username
            self.name = name
            self.password = password
            self.email = email
        else:
            args = { "username": username }
            response = server.post_request("get-member", args)
            if response["code"] == HTTPStatus.OK:
                print(response)  # For debug
                self.name = response["name"];
                self.password= response["password"];
                self.email= response["email"];
                self.isvalid = True
            else:
                self.isvalid = False
