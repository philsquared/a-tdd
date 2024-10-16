#include <gtest/gtest.h>

#include "model.h"

#include <iostream>
#include <string>

using namespace TddAir;

const std::string server_url = "localhost:5001";
// const std::string server_url = "tddair.atdd.dev:5200";

class Environment : public ::testing::Environment {
public:
    void SetUp() override {
        Request req(server_url);
        auto status_json = req.post_no_retry("/admin/status");
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

testing::Environment* const env =
    testing::AddGlobalTestEnvironment(new Environment);


TEST(MemberTests, retrieveAMember) {
    Request req(server_url);
    Member member(req, "benstone");
    EXPECT_EQ(member.name(), "Ben Stone");
}

TEST(FlightTests, retrieveAFlight) {
    Request req(server_url);
    Flight f(req, "MA828");
    EXPECT_EQ(f.origin(), "AUS");
    EXPECT_EQ(f.destination(), "ATL");
}
