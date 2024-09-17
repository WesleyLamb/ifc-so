#include "Task.hpp"

#include <iostream>
#include <regex>
#include "datetime.h"

void Task::processData(std::smatch *match)
{
    auto hour = stoi((*match)[5].str());
    outputData[hour]->accessCount++;
    if ((*match)[10].str() == "200") {
        outputData[hour]->sucessCount++;
    }
}

Task::Task()
{
    for (int i = 0; i < 24; i++) {
        outputData[i] = new OutputData();
    }
}

Task::~Task()
{
    std::string* linha;
    while (this->_lines.size() > 0) {
        linha = this->_lines.front();
        this->_lines.pop();
        delete linha;
    }
    for (int i = 0; i < 24; i++) {
        delete this->outputData[i];
    }
}

void Task::addData(std::string *line)
{
    this->_lines.push(line);
}

void Task::process()
{
    int currentLine = 0;
    while (this->_lines.size() > 0) {
        std::string *line = this->_lines.front();
        this->_lines.pop();
        std::smatch match;
        if (std::regex_search(*line, match, this->_pattern)) {
            if (match.size() != 15){
                std::cout << "Linha X veio com informação diferente do esperado!";
            } else {
                this->processData(&match);
            }
        } else {
            std::cout << *line << std::endl;
        }
        delete line;
        currentLine++;
    }
    // std::cout << "Task finished" << std::endl;
}
