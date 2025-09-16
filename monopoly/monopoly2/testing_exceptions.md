# Testing Exceptions with GTest and GMock

To test that a statement throws an exception you need to enclose the statement in a lambda 
and use the `Throws<E>()` or `ThrowsMessage<E>()` [matchers](https://google.github.io/googletest/reference/matchers.html#exception-matchers).  

    using namespace testing;
    EXPECT_THAT( [&]{ /* statement that should throw */ },
        ThrowsMessage<E>( m ) );

Where `E` is the exception type and `m` is a matcher that is applied to the result of calling `what()`
(or you can pass a string to match equal against)

[See here for some useful matchers to apply against the string](https://google.github.io/googletest/reference/matchers.html#string-matchers)