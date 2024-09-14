#ifndef OutputDataDay_hpp
#define OutputDataDay_hpp

#define HOURS_PER_DAY 24

#include <boost/date_time/gregorian/gregorian.hpp>

#include <chrono>

struct OutputDataDay {
    boost::gregorian::date day;
    int hour[HOURS_PER_DAY];
    int accessCount;
    int successCount;
};

#endif