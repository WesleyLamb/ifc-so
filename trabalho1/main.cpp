#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include "src/Task.hpp"
#include "src/ThreadPool.hpp"

int main() {
    std::regex pattern {"^([0-9\\.]*)(?:\\s\\-.\\-\\s)(?:\\[)([\\w\\d\\s\\/\\:\\+\\-]*)(?:\\s\\+)([\\d]*)(?:\\])(?:\\s\")([\\w]*)(?:\\s)(.[^\"]*)(?:\"\\s)([\\d]*)(?:\\s)([\\d]*)(?:\\s\")(.[^\"]*)(?:\"\\s\")(.[^\"]*)(?:.*$)"};
    int i;

    std::ifstream file('./access.log');

    std::string line;
    if (!file.is_open()) {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
        return 1;
    }
    ThreadPool pool(std::thread::hardware_concurrency());
    pool.Start();
    Task* task;
    while (getline(file, line)) {
        if ((i % 10000) == 0) {
            task = new Task();
        }
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            if (match.size() != 9){
                std::cout << "Linha " << (i + 1) << " veio com informação diferente do esperado!";
            } else {
                task.addData(match);
            }
        }
        i++;
    }

    while (pool.busy()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "All tasks have been processed" << std::endl;
    pool.Stop();
    // std::string input = "146.185.139.243 - - [23/Jan/2019:12:30:18 +0330] \"GET /image/44/productType/120x90 HTTP/1.1\" 200 13363 \"https://www.zanbil.ir/m/product/7834/\%DA\%A9\%D9\%88\%D9\%84\%D8\%B1-\%D8\%A2\%D8\%A8\%DB\%8C-\%D8\%AB\%D8\%A7\%D8\%A8\%D8\%AA-\%D9\%84\%D9\%88\%D8\%B1\%DA\%86-\%D9\%85\%D8\%AF\%D9\%84-7000\" \"Mozilla/5.0 (Linux; Android 4.4.2; en-us; HUAWEI Hol-U19 Build/HUAWEIHol-U19) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/30.0.0.0 Mobile Safari/537.36;\" \"-\"";





    // Ler o arquivo
    // Juntar pacotes com 10000 linhas
    // Lançar esses pacotes em uma lista
    // Ter um pool de threads que vão processar esses pacotes
    // Cada thread vai pegar um pacote e processar, colocar um semáforo na hora de tirar o pacote
    // Cada thread vai  ter um contador de quantos pacotes ele processou
    return 0;
}