You have an email from your boss. You need to make the following changes to this highly critical financial code:

1. The transfer function is screwing up when too much is transferred from an account - we need to check and throw an exception
2. If an exception is thrown either all funds must be transferred, or none (transactional)
3. People are complaining that BankAccount takes too long to build against. Remove iostreams from the header.

The next day you get another email with some more work items - some more critical than others

4. They are still complaining - seems the logging header needs cleaning up.
5. We have a requirement that whenever a balance changes it leaves an audit trail in the logs. The log must include the account number, the old balance and the new balance and must always be written.
6. Remove duplication in the logging macros.
