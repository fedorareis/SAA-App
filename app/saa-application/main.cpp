/**
 * Entry point of the saa-application
 */
#include <common/Common.h>
#include "saa-application/SaaApplication.h"

int main(int argC, const char* argV[])
{
   SaaApplication app;
   app.initSocks();
   //Common common;
   //common.report();

   SaaApplication::shutdown();

   return 0;
}