#ifndef TDDAIRCLIENT_MODEL_H
#define TDDAIRCLIENT_MODEL_H

#include <string>
#include "request.h"

namespace TddAir {

    class Member {
        std::string m_username;
        std::string m_name;
        std::string m_password;
        std::string m_email;
        bool m_isvalid = false;
        Request& m_req;
    public:
        // Looks up in DB
        Member(Request& req, std::string const& username);

        // Creates in DB
        Member(Request& req, std::string const& username, std::string const& name, std::string const& password, std::string const& email );

        explicit operator bool() const { return m_isvalid; }

        [[nodiscard]] std::string const& name() const { return m_name; }
    };

    class Flight {
        std::string m_origin;
        std::string m_destination;
        int m_mileage;
        std::string m_airline;
        int m_number;
        bool m_isvalid;
    public:
        // Looks up in DB
        Flight(Request& req, std::string const& full_flight_number);

        // Creates in DB
        Flight(Request& req, std::string const& origin, std::string const& destination, int mileage, std::string const& airline, int number);

        explicit operator bool() const { return m_isvalid; }

        [[nodiscard]] std::string full_flight_number() const;

        [[nodiscard]] std::string origin() const { return m_origin; }
        [[nodiscard]] std::string destination() const { return m_destination; }
    };
}

#endif
