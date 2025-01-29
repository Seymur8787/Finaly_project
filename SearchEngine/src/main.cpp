#include <iostream>
#include "indexer.h"
#include "request_handler.h"

int main() {
    // Создаем объект индексатора
    Indexer indexer;

    // Добавление документов
    indexer.addDocument("doc1.txt", "This is a sample document with sample text.");
    indexer.addDocument("doc2.txt", "This document contains a different sample text.");

    // Создаем объект обработчика запросов
    RequestHandler requestHandler(indexer);

    // Пример запроса для поиска
    std::string query = "sample";
    std::cout << "Processing query: " << query << "\n";

    // Обрабатываем запрос и получаем результаты
    std::vector<std::string> results = requestHandler.processRequest(query);

    if (results.empty()) {
        std::cout << "No results found for query: " << query << "\n";
    }
    else {
        std::cout << "Found " << results.size() << " results. Saving to JSON...\n";

        // Сохраняем результаты в JSON
        requestHandler.saveResultsToJson(results, "results.json");
        std::cout << "Results saved to 'results.json'.\n";
    }

    return 0;
}
