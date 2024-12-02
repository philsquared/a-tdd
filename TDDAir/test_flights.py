from flight import Flight


def test_flight():
    dfw_ord = Flight("DFW", "ORD", 915, "AA", 1720)

    assert dfw_ord.full_flight_number == "AA1720"
