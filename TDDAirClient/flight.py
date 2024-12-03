from http import HTTPStatus
from multipledispatch import dispatch

from server import Server


class Flight:
    @dispatch( Server, str)
    def __init__(self, server: Server, full_flight_number: str):
        self.airline = full_flight_number[0:2]
        self.number = int(full_flight_number[2:])
        args = { "airline": self.airline, "number": self.number }
        response = server.post_request("get-flight", args)
        if response["code"] == HTTPStatus.OK:
            print(response)  # For debug
            self.origin = response["origin"]
            self.destination= response["destination"]
            self.mileage = response["mileage"]
            self.isvalid = True
        else:
            self.isvalid = False

    @dispatch( Server, str, str, int, str, int)
    def __init__(self, server: Server, origin: str, destination: str, mileage: int, airline: str, number: int):
        args = {
            "origin": origin,
            "destination": destination,
            "mileage": mileage,
            "airline": airline,
            "number": number
        }
        response = server.post_request("create-flight", args)
        self.isvalid = (response["code"] == HTTPStatus.OK)
        self.origin = origin
        self.destination = destination
        self.mileage = mileage
        self.airline = airline
        self.number = number
