// This file is not part of the project - it's an alternate implementation of tests.cpp
// using GoogleMock.
// Note: you'll also need to make the post method of Request virtual.
#include <gtest/gtest.h>

#include "model.h"

#include <iostream>
#include <string>

using namespace TddAir;

const std::string server_url = "abc.def"; // No longer used

#include <gmock/gmock.h>
class FakeRequest : public Request {
public:
    FakeRequest() : Request("") {}
    MOCK_METHOD(json, post, (std::string const& target, json const& data, bool api_check, int attempt), (override));
};

class Environment : public ::testing::Environment {
public:
    void SetUp() override {
        Request req(server_url);
        auto status_json = req.post("/admin/status");
        std::cout << status_json << std::endl;
        std::cout << req.post("/admin/create_db", {{"delete-if-exists", true}}) << std::endl;

        // Force these members to be in the DB
        Member(req, "benstone", "Ben Stone", "abc123", "ben.stone@manifest.com");
        Member(req, "michaelastone", "Michaela Stone", "password", "michaela.stone@manifest.com");

        // Force these flights to be in the DB
        Flight(req, "AUS", "ATL", 819, "MA", 828);
        Flight(req, "ATL", "LHR", 4218, "VS", 104);
    }
    void TearDown() override {
        Request req(server_url);
        std::cout << req.post("/admin/drop_db") << std::endl;
    }
};

// testing::Environment* const env =
//     testing::AddGlobalTestEnvironment(new Environment);

using ::testing::AtLeast;
using ::testing::_;
using ::testing::Return;

TEST(MemberTests, retrieveAMember) {
    FakeRequest req;
    EXPECT_CALL(req, post("/get-member",_,_,_))
      .Times(AtLeast(1))
        .WillOnce(Return(json{
            {"code", 200},
            {"name", "Ben Stone"},
            {"password", "123"},
            {"email", "a@b.c"},
            }));

    Member member(req, "benstone");
    EXPECT_EQ(member.name(), "Ben Stone");
}

TEST(FlightTests, retrieveAFlight) {
    FakeRequest req;
    EXPECT_CALL(req, post("/get-flight",_,_,_))
      .Times(AtLeast(1))
        .WillOnce(Return(json{
            {"code", 200},
            {"origin", "AUS"},
            {"destination", "ATL"},
            {"mileage", 123},
            {"airline", "VA"},
            }));

    Flight f(req, "MA828");
    EXPECT_EQ(f.origin(), "AUS");
    EXPECT_EQ(f.destination(), "ATL");
}
