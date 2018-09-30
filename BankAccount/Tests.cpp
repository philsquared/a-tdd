#include "BankAccount.h"
#include "catch.hpp"

TEST_CASE() {

    Account bob( 123 );
    Account alice( 456 );

    bob.setBalance( 400 );
    alice.setBalance( 500 );

    transferFunds( bob, alice, 100.0 );

    REQUIRE( bob.balance() == 300 );
    REQUIRE( alice.balance() == 600 );
}
