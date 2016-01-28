//
// Created by Kyle Piddington on 1/20/16.
//

#ifndef SAA_APPLICATION_VALIDATIONWRITER_H
#define SAA_APPLICATION_VALIDATIONWRITER_H


#include <iostream>
#include "Validator.h"


class ValidationWriter {
   public:
   static void writeErrors(std::ostream &str, const Validator &v);
};


#endif //SAA_APPLICATION_VALIDATIONWRITER_H
