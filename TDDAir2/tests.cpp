#include <gtest/gtest.h>

#include "Flight.h"

TEST(FlightTests, Flight) {

    Flight dfw_ord{"DFW", "ORD", 915, "AA", 1720};

    EXPECT_EQ( dfw_ord.full_flight_number(), "AA1720");
}
