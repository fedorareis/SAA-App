//
// Created by Kyle Piddington on 11/15/15.
//

#include <iostream>
#include "SaaApplication.h"
#include "Correlation.h"
#include "Decision.h"

void SaaApplication::report()
{
    std::cout << "Hello from Saa App!" << std::endl;
    Correlation cor;
    Decision dec;
    cor.report();
    dec.report();
}