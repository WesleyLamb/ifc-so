#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "OutputData.hpp"
#include "Task.hpp"
#include "datetime.h"

class ThreadPool {
public:
    ThreadPool(int num_threads);
    ~ThreadPool();
    void start();
    void queueTask(Task *task);
    void stop();
    bool busy();
    void outputResults();


private:
    void threadLoop();                          // Função que as threads vão rodar
    void mergeTaskOutput(Task* task);           // Mescla os resultados de uma task para sí

    int num_threads;
    bool should_terminate = false;              // Variável que sinaliza se as threads devem parar de procurar tarefas
    std::mutex queue_mutex;                     // Mutex para sessão crítica na hora de despachar/processar as tarefas
    std::mutex output_mutex;                    // Mutex para sessão crítica na hora de mesclar os resultados da task
    std::condition_variable mutex_condition;    // cv para manter as threads aguardando novas tarefas ao invés de ficarem procurando tarefas
    std::vector<std::thread> threads;           // vetor com todas as threads
    std::queue<Task*> tasks;
    OutputData** data;
};

#endif