#ifndef Task_hpp
#define Task_hpp

#include <queue>
#include <string>
#include "InputData.hpp"

class Task {
    private:
        std::queue<InputData> _lines;
    public:
        Task();
        void addData(std::string& line);
        void process();
};

#endif