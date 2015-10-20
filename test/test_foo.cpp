#include "catch/catch.hpp"
#include "foo.h"


TEST_CASE( "Foo test Succeeds", "[fooTests]" ) {
   Foo foo;
   REQUIRE( foo.bar(1) == 2 );
   REQUIRE( foo.bar(2) == 4 );
   REQUIRE( foo.bar(3) == 6 );
   REQUIRE( foo.bar(10) == 20 );
}
TEST_CASE ("Foo test fails", "[fooTests]"){
   Foo foo;
   REQUIRE( foo.bar(1) == 1);
}
