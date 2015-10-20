#pragma once
class Adder
{
public:
   /**
    * Create a new adder with a starting value
    */
   Adder(int initialValue);
   /**
    * Add a number to the adder, and return the result
    * @param  numToAdd the amount to add to the adder
    * @return          the current value of the adder  + numToAdd
    */
   int addTo(int numToAdd);
   /**
    * Get the current value of the adder
    * @return the internal Value
    */
   int getValue() const;
private:
   int internalValue;

};
