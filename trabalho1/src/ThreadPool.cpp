#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int num_threads)
{
    this->num_threads = num_threads;
}

void ThreadPool::Start()
{
    // const uint32_t num_threads = std::thread::hardware_concurrency(); // Max # of threads the system supports
    for (uint32_t ii = 0; ii < this->num_threads; ++ii) {
        threads.emplace_back(std::thread(&ThreadPool::ThreadLoop,this));
    }
}

void ThreadPool::QueueTask(std::shared_ptr<Task> task)
{
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex);
        this->tasks.push(task);
    }
    this->mutex_condition.notify_one();
}

void ThreadPool::Stop()
{
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex);
        this->should_terminate = true;
    }
    this->mutex_condition.notify_all();
    for (std::thread& active_thread : this->threads) {
        active_thread.join();
    }
    this->threads.clear();
}

bool ThreadPool::busy()
{
    bool poolbusy;
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        poolbusy = !this->tasks.empty();
    }
    return poolbusy;
}

void ThreadPool::ThreadLoop() {
    while (true) {
        std::function<void()> job;
        {
            std::shared_ptr<Task> task;
            // As chaves abaixo são para forçar o RAII do lock
            {
                std::unique_lock<std::mutex> lock(this->queue_mutex);
                this->mutex_condition.wait(lock, [this] {
                    return !tasks.empty() || this->should_terminate;
                });
                if (this->should_terminate) {
                    return;
                }
                task = this->tasks.front();
                this->tasks.pop();
            }
            task->process();
        }
        job();
    }
}