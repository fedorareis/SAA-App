#include "catch/catch.hpp"
#include "adders/adder.h"
SCENARIO( "Adder can be declared and added to", "[adder]" ) {
   Adder adder(0);

   WHEN("The adder is initialized") {
      adder = Adder(5);
      THEN (" The initial value is the initialization value") {
         REQUIRE(adder.getValue() == 5);
      }
   }
   WHEN("The adder is added to"){
      int res = adder.addTo(2);
      THEN ("The result is the added number"){
         REQUIRE(res == 2);
      }
      THEN("The adder's new value has changed"){
         REQUIRE(adder.getValue() == 2);
      }
   }
}

