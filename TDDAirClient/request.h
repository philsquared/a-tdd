#ifndef TDDAIRCLIENT_REQUEST_H
#define TDDAIRCLIENT_REQUEST_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace TddAir {
    class Request {
        std::string m_host;
        std::string m_port;
        std::string m_initial_target;

    public:
        Request(std::string_view base_url);

        [[nodiscard]] std::string host() const { return m_host; }
        [[nodiscard]] std::string port() const { return m_port; }
        [[nodiscard]] std::string target() const { return m_initial_target; }

        json post(std::string const& target = {}, json const& data = {}, bool api_check = true, int attempt=0);
        json post_no_retry(std::string const& target = {}, json const& data = {}, bool api_check = true);
    };

}
#endif
