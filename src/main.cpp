#include "foo.h"
#include "adders/adder.h"
#include <iostream>

int main()
{
   Foo foo;
   std::cout << "foo.bar(5) == "  << foo.bar(5) << std::endl;
   Adder adder(0);
   for(int i = 0; i < 10; i++)
   {
      std::cout << "Adder is " << adder.getValue() << ", adding 1" << std::endl;
      adder.addTo(1);

   }
    std::cout << "Adder is " << adder.getValue() << ", and done" << std::endl;
     
} 