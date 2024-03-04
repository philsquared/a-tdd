#include <gtest/gtest.h>

#include "Flight.h"

enum class Status{ FutureMember, Red, Green, Blue, Gold };

std::ostream& operator << (std::ostream& os, Status status) {
    switch( status ) {
        case Status::FutureMember: return os << "FutureMember";
        case Status::Red: return os << "Red";
        case Status::Green: return os << "Green";
        case Status::Blue: return os << "Blue";
        case Status::Gold: return os << "Gold";
        default: return os << "** unrecognised status enum with value " << static_cast<int>(status) << "**";
    }
}

const int greenThreshold = 25'000;
const int blueThreshold = 50'000;
const int goldThreshold = 75'000;

Status status_for_miles(int miles) {
    assert(miles >= 0);
    if( miles < greenThreshold )
        return Status::Red;
    if( miles < blueThreshold )
        return Status::Green;
    if( miles < goldThreshold )
        return Status::Blue;
    return Status::Gold;
}

TEST(TDDAir, statusIsRedForLessThan25Kmiles) {
    EXPECT_EQ(status_for_miles(0), Status::Red);
    EXPECT_EQ(status_for_miles(1), Status::Red);
    EXPECT_EQ(status_for_miles(24'999), Status::Red);
}
TEST(TDDAir, statusIsGreenBetween25Kand50Kmiles) {
    EXPECT_EQ(status_for_miles(25'000), Status::Green);
    EXPECT_EQ(status_for_miles(25'001), Status::Green);
    EXPECT_EQ(status_for_miles(49'999), Status::Green);
}
TEST(TDDAir, TheRest) {
    EXPECT_EQ(status_for_miles(50'000), Status::Blue);
    EXPECT_EQ(status_for_miles(75'000), Status::Gold);
}


class Member {
    Status m_status = Status::FutureMember;
    int m_milesYtd = 0;
public:
    Member(std::string username, std::string email) {}
    Status status() const {
        return m_status;
    }
    void enroll() {
        m_status = Status::Red;
    }
    void complete_flight(Flight const& flight) {
        m_milesYtd += flight.mileage;
        m_status = status_for_miles(m_milesYtd);
    }
};

class TDDAirMembers : public testing::Test {
protected:
    Member member = Member("username", "user@test.com");
    void SetUp() override {}
};

TEST_F(TDDAirMembers, MembersAreFutureMembersUntilEnrolled) {
    EXPECT_EQ(member.status(), Status::FutureMember);
}
TEST_F(TDDAirMembers, MembersAreRedOnceEnrolled) {
    member.enroll();
    EXPECT_EQ(member.status(), Status::Red);
}
TEST_F(TDDAirMembers, MembersChangedStatusWhenMilesAreAdded) {
    member.enroll();
    Flight dfw_ord{"DFW", "ORD", 25'000, "AA", 1720};
    member.complete_flight(dfw_ord);

    EXPECT_EQ(member.status(), Status::Green);
}
