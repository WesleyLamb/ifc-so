#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include "src/Task.hpp"
#include "src/ThreadPool.hpp"

int main() {
    int i = 0;
    // Abre o arquivo
    std::ifstream file("./access.log");

    std::string *line;
    if (!file.is_open()) {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
        return 1;
    }

    // Cria o ThreadPool para gerenciar as threads
    ThreadPool pool(std::thread::hardware_concurrency());
    // Inicia as threads dentro do ThreadPool
    pool.start();

    Task *task = NULL;
    while (!file.eof()) {
        line = new std::string();
        getline(file, *line);
        if ((i % 1000) == 0) {
            // A cada 10k de linhas, lança a task pro pool
            if (task != NULL) {
                pool.queueTask(task);
            }
            task = new Task();
        }
        // Adiciona uma linha à task
        task->addData(line);

        i++;
    }

    // Se sobrou uma task sem 10k de linhas
    if ((task != NULL) && (!task->queued)) {
        pool.queueTask(task);
    }

    // Aguarda as threads terminarem de processar
    while (pool.busy()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    // O tcho acima verifica a fila, então pode ser que as threads ainda estejam processando o último lote
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // Mata tudo
    pool.stop();
    // Exibe os resultados no stdout
    pool.outputResults();
    return 0;
}