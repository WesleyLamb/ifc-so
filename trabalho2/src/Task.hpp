#ifndef Task_hpp
#define Task_hpp

#include <queue>
#include <regex>
#include <string>
#include "OutputData.hpp"
#include "datetime.h"

class Task {
    private:
        std::queue<std::string*> _lines;
        const std::regex _pattern {"^([0-9\\.]*)(?:\\s[^\\s]*\\s[^\\s]*\\s)(?:\\[)(\\d{2})(?:\\/)([a-zA-z]{3})(?:\\/)(\\d{4})(?:\\:)(\\d{2})(?:\\:)(\\d{2})(?:\\:)(\\d{2})(?:\\s)([\\+\\d]*)(?:\\])(?:\\s\")([^\"]*)(?:\"\\s)([\\d]*)(?:\\s)([\\d]*)(?:\\s\")([^\"]*\")(?:\\s\")([^\"]*\")(?:\\s\")(.[^\"]*\")$"};

        void processData(std::smatch *match);
    public:
        Task();
        ~Task();
        void addData(std::string *line);
        void process();
        bool queued = false;
        OutputData* outputData[24];
};

#endif