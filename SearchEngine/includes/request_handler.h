#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "indexer.h"
#include <vector>
#include <string>

class RequestHandler {
public:
    // Конструктор
    explicit RequestHandler(Indexer& indexer);

    // Метод для обработки запроса
    std::vector<std::string> processRequest(const std::string& request);

    // Метод для сохранения результатов в JSON
    void saveResultsToJson(const std::vector<std::string>& results, const std::string& outputFile);

private:
    // Ссылка на индексатор
    Indexer& indexer;

    // Приватные методы
    std::vector<std::string> splitRequestIntoWords(const std::string& request) const;
    std::string toLower(const std::string& input) const;
};

#endif // REQUEST_HANDLER_H
