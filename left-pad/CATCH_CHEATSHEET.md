For more details you can see [the tutorial](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md) 
or [the reference docs](https://github.com/catchorg/Catch2/tree/master/docs).

```
#include "catch.hpp"

TEST_CASE( "<name>" ) { // To start a test case with name <name>
    
    CHECK( add( 2, 3 ) == 6 ); // CHECK reports failure but continues
    REQUIRE( add( 2, 3 ) == 5 ); // REQUIRE reports and aborts on failure

    int i = 7; // Common value

    SECTION( "first section" ) { // Starts a section call "first section"
        CHECK( theAnswer() == 42 );
    }

    SECTION( "second section" ) { // Starts another section
        // The whole test case will be executed twice:
        //  - once for "first section", then again for "second section"
        // Only one of these sections will be entered each time
        INFO( "Only reported on failure" );
        CAPTURE( i ); // reports value of i on failure
    
        FAIL( "This always fails" );
    }
}
```