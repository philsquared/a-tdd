
class Flight:

    def __init__(self,
                 from_airport: str,
                 to_airport: str,
                 distance: int,
                 airline_code: str,
                 flight_number: int):
        self.from_airport = from_airport
        self.to_airport = to_airport
        self.distance = distance
        self.airline_code = airline_code
        self.flight_number = flight_number


    @property
    def full_flight_number(self) -> str:
        return f"{self.airline_code}{self.flight_number}"
