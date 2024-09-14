#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "OutputData.hpp"
#include "Task.hpp"

class ThreadPool {
public:
    ThreadPool(int num_threads);
    void Start();
    void QueueTask(std::shared_ptr<Task> task);
    void Stop();
    bool busy();

private:
    void ThreadLoop();

    int num_threads;
    bool should_terminate = false;           // Tells threads to stop looking for jobs
    std::mutex queue_mutex;                  // Prevents data races to the job queue
    std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination
    std::vector<std::thread> threads;
    std::queue<std::shared_ptr<Task>> tasks;
};

#endif