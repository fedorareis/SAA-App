/**
 * Entry point of the CDTI application
 */
#include <common/Common.h>
#include "cdti/CDTI.h"
int main(int argC, const char* argV[])
{

   Cdti cdti;
   cdti.report();
   Common common;
   common.report();
   return 0;
}