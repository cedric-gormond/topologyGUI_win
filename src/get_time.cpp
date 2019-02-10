//
// Created by Cedric Gormond on 28/01/2019.
//

#include "get_time.h"

const std::string currentDateTime(){
time_t     now = time(0);
struct tm  tstruct;
char       buf[80];
tstruct = *localtime(&now);
// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime for more information about date/time format
//strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
strftime(buf, sizeof(buf), "%d-%m-%Y.%X", &tstruct);

return buf;
}
