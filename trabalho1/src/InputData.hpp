#ifndef InputData_hpp
#define InputData_hpp

#include <regex>

class InputData {
    public:
        InputData(std::smatch *input);
        std::string ip;
        time_t timestamp;
        std::string httpMethod;
        std::string endpoint;
        std::string httpStatus;
        std::string bytesSent;
        std::string httpReferer;
        std::string httpUserAgent;
};

#endif