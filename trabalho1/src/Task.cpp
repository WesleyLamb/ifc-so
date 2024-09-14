#include "Task.hpp"

#include <iostream>
#include <stdio.h>
#include <unistd.h>

Task::Task(int id)
{
    this->id = id;
}

void Task::process()
{
    std::cout << "Task" << this->id << "being executed" << std::endl;

    sleep(1);
}