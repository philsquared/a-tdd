#include "Flight.h"

Flight::Flight(std::string origin, std::string destination, int mileage, std::string airline, int number)
:   origin(std::move(origin)),
    destination(std::move(destination)),
    mileage(mileage),
    airline(std::move(airline)),
    number(number)
{}

std::string Flight::full_flight_number() const {
    return airline + std::to_string(number);
}
