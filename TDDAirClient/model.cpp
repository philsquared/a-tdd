#include "model.h"
#include <charconv>
#include <iostream>

namespace TddAir {

    Member::Member(Request& req, std::string const& username)
    :   m_req(req),
        m_username(username)
    {
        json args = { { "username", username } };
        auto member_data = req.post("/get-member", args);
        if( member_data["code"] == 200 ) {
            std::cout << member_data << std::endl; // For debug
            m_name = member_data["name"];
            m_password= member_data["password"];
            m_email= member_data["email"];
            m_isvalid = true;
        }
    }

    Member::Member(Request& req, std::string const& username, std::string const& name, std::string const& password, std::string const& email )
    :   m_req(req),
        m_username(username),
        m_name(name),
        m_password(password),
        m_email(email)
    {
        json args = {
            { "username", username },
            { "name", name },
            { "password", password },
            { "email", email },
            { "data", {} }
        };
        auto member_data = req.post("/create-member", args);
        if( member_data["code"] == 200 ) {
            m_isvalid = true;
        }
    }

    Flight::Flight(Request& req, std::string const& full_flight_number) {
        size_t pos = full_flight_number.find_first_of("0123456789");
        if( pos == std::string::npos )
            m_isvalid = false;

        m_airline = full_flight_number.substr(0, pos);
        std::from_chars(full_flight_number.data()+pos, full_flight_number.data() + full_flight_number.size(), m_number);

        json args = { {"airline", m_airline}, {"number", m_number} };
        auto flight_data = req.post("/get-flight", args);
        if( flight_data["code"] == 200 ) {
            m_origin = flight_data["origin"];
            m_destination = flight_data["destination"];
            m_mileage = flight_data["mileage"];
            m_airline = flight_data["airline"];
            m_isvalid = true;
        }

    }

    Flight::Flight(Request& req, std::string const& origin, std::string const& destination, int mileage, std::string const& airline, int number)
    :   m_origin(origin),
        m_destination(destination),
        m_mileage(mileage),
        m_airline(airline),
        m_number(number)
    {
        json args = {
            { "origin", origin },
            { "destination", destination },
            { "mileage", mileage },
            { "airline", airline },
            { "number", number }
        };
        auto member_data = req.post("/create-flight", args);
        if( member_data["code"] == 200 ) {
            m_isvalid = true;
        }
    }

    std::string Flight::full_flight_number() const {
        return m_airline + std::to_string(m_number);
    }

}
