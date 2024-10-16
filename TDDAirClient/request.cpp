#include "request.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <thread>
#include <chrono>
#include <iostream>
#include <array>

using namespace std::chrono_literals;

std::array<std::chrono::milliseconds, 6> backoff_delays = { 10ms, 100ms, 200ms, 300ms, 500ms, 500ms };

// Boost.Beast usage based on example here:
// https://www.boost.org/doc/libs/master/libs/beast/example/http/client/methods/http_client_methods.cpp

namespace TddAir {
    namespace beast = boost::beast;     // from <boost/beast.hpp>
    namespace http = beast::http;       // from <boost/beast/http.hpp>
    namespace net = boost::asio;        // from <boost/asio.hpp>
    using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

    std::string required_api_version = "0.2";

    // Parse url string into host, port and (optionally) initial target
    Request::Request(std::string_view base_url) {
        if( base_url.length() >= 8 && base_url.substr(0, 8) == "https://" ) {
            m_host = base_url.substr(8);
            m_port = "443";
        }
        else if( base_url.length() >= 7 && base_url.substr(0, 7) == "http://" ) {
            m_host = base_url.substr(7);
            m_port = "80";
        }
        else {
            m_host = base_url;
            m_port = "80";
        }
        if( auto pos = m_host.find_first_of('/'); pos != std::string::npos ) {
            m_initial_target = m_host.substr(pos);
            m_host = m_host.substr(0, pos);
        }
        if( auto pos = m_host.find_first_of(':'); pos != std::string::npos ) {
            m_port = m_host.substr(pos+1);
            m_host = m_host.substr(0, pos);
        }
    }

    json Request::post(std::string const& target, json const& data, bool api_check, int attempt) {
        std::string data_str = data.dump();

        net::io_context ioc;
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        auto const results = resolver.resolve(m_host, m_port);
        stream.connect(results);

        // Write
        std::string full_target = m_initial_target + target;
        http::request<http::string_body> req{http::verb::post, full_target, 11};
        req.set(http::field::host, m_host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::content_type, "application/json");
        req.body() = data_str;
        req.prepare_payload();
        http::write(stream, req);

        // Read
        beast::flat_buffer buffer;
        http::response<http::string_body> result;
        http::read(stream, buffer, result);

        beast::error_code ec;
        std::ignore = stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};

        json response_data = json::parse(result.body());

        if( response_data["code"] != 200 && attempt < backoff_delays.size() ) {
            std::this_thread::sleep_for(backoff_delays[attempt]);
            std::cout << "failed. Retry attempt #" << attempt << std::endl;
            return post(target, data, api_check, attempt+1);
        }
        if( api_check ) {
            auto api_version = response_data.value("api_version", "<no API version returned>");
            if (api_version != required_api_version)
                throw std::runtime_error(
                        "incompatible API, required: " + required_api_version + " but got: " + api_version);
        }
        return response_data;
    }
}
