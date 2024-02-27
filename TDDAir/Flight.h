#ifndef TDDAIR_FLIGHT_H
#define TDDAIR_FLIGHT_H

#include <string>

class Flight {
public:
    std::string origin;
    std::string destination;
    int mileage;
    std::string airline;
    int number;

    Flight(std::string origin, std::string destination, int mileage, std::string airline, int number);

    std::string full_flight_number() const;
};

#endif //TDDAIR_FLIGHT_H
