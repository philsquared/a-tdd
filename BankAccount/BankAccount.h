#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include "Logger.h"

class Account {
    double m_balance = 0;
    int m_accountNumber;
public:
    Account( int accountNumber ) : m_accountNumber( accountNumber ) {}

    auto accountNumber() const { return m_accountNumber; }
    auto balance() const { return m_balance; }
    void setBalance( double amount ) {
        LOG_DEBUG( "balance was: " << m_balance );
        LOG_INFO( "setting balance to: " << amount << " in Acc# " << m_accountNumber );
        m_balance = amount;
        LOG_DEBUG( "balance is now: " << m_balance );
    }

    friend void transferFunds( Account& fromAccount, Account& toAccount, double amount ) {
        LOG_INFO( "Transferring " << amount << " from Acc# " << fromAccount << " to " << toAccount );
        toAccount.m_balance += amount;
        fromAccount.m_balance -= amount;
    }

    friend auto operator<< ( std::ostream& os, Account& account ) -> std::ostream& {
        return os << account.accountNumber();
    }
};

#endif // BANKACCOUNT_H
