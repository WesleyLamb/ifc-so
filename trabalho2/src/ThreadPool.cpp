#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int num_threads)
{
    this->data = (OutputData**) malloc(sizeof(OutputData*) * 24);
    for (int i = 0; i < 24; i++) {
        this->data[i] = new OutputData();
    }
    this->num_threads = num_threads;
}

ThreadPool::~ThreadPool()
{
    for (int i = 0; i < 24; i++) {
        delete this->data[i];
    }
    delete this->data;
}

void ThreadPool::start()
{
    for (uint32_t ii = 0; ii < this->num_threads; ++ii) {
        threads.emplace_back(std::thread(&ThreadPool::threadLoop, this));
    }
}

void ThreadPool::queueTask(Task *task)
{
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex);
        this->tasks.push(task);
        task->queued = true;
    }
    this->mutex_condition.notify_one();
}

void ThreadPool::stop()
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

void ThreadPool::threadLoop() {
    while (true) {
        std::function<void()> job;
        {
            Task *task;
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
            this->mergeTaskOutput(task);
            delete task;
        }
    }
}


void ThreadPool::mergeTaskOutput(Task *task)
{
    std::unique_lock<std::mutex> lock(output_mutex);
    for (int i = 0; i < 24; i++) {
        this->data[i]->accessCount += task->outputData[i]->accessCount;
        this->data[i]->sucessCount += task->outputData[i]->sucessCount;
    }
}

void ThreadPool::outputResults()
{
    int total = 0;
    int sucesso = 0;
    for (int i = 0; i < 24; i++) {
        std::cout << i << " success => " << this->data[i]->sucessCount << " total => " << this->data[i]->accessCount << std::endl;
        total += this->data[i]->accessCount;
        sucesso += this->data[i]->sucessCount;
    }
    std::cout << "Sucesso: " << sucesso << " Total: " << total << std::endl;
}
