#include "BankAccount.h"
#include <gtest/gtest.h>

TEST(BankAccountTests, TransferFunds) {

    Account bob( 123 );
    Account alice( 456 );

    bob.setBalance( 400 );
    alice.setBalance( 500 );

    transferFunds( bob, alice, 100.0 );

    EXPECT_EQ( bob.balance(), 300 );
    EXPECT_EQ( alice.balance(), 600 );
}
