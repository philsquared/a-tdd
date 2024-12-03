from http import HTTPStatus

import pytest

from flight import Flight
from member import Member
from server import Server


@pytest.fixture
def fresh_db():
    print("creating db")
    server = Server()
    response = server.post_request('admin/create_db', {"delete-if-exists": True})
    assert response["status"] == "Created database"
    assert response["code"] == HTTPStatus.OK

    # Force these members to be in the DB
    assert Member(server, "benstone", "Ben Stone", "abc123", "ben.stone@manifest.com").isvalid
    assert Member(server, "michaelastone", "Michaela Stone", "password", "michaela.stone@manifest.com").isvalid

    # Force these flights to be in the DB
    assert Flight(server, "AUS", "ATL", 819, "MA", 828).isvalid
    assert Flight(server, "ATL", "LHR", 4218, "VS", 104).isvalid

    yield

    print("dropping db")
    server.post_request('admin/drop_db', {})

def test_retrieve_a_member(fresh_db):
    server = Server()
    member = Member(server, "benstone");
    assert member.name == "Ben Stone"


def test_retrieve_a_flight(fresh_db):
    server = Server()
    flight = Flight(server, "MA828")
    assert flight.origin == "AUS"
    assert flight.destination == "ATL"
