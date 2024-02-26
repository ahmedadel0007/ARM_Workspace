#include "Log.h"

int main (void)
{
     int a =5;
     const char* name="ahmed";
    Logger::Trace ("log_test %d %s ",a,name);
return 0;
}