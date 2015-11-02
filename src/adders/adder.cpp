#include "adders/adder.h"


Adder::Adder(int initialValue):
   internalValue(initialValue)
   {

   }

int Adder::addTo(int numToAdd)
{
   internalValue += numToAdd;
   return internalValue;
}

int Adder::getValue() const
{
   return internalValue;
}
