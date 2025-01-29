#include <nlohmann/json.hpp>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <set>
#include "request_handler.h"

using json = nlohmann::json;

// Конструктор RequestHandler, инициализирует объект Indexer
RequestHandler::RequestHandler(Indexer& indexer) : indexer(indexer) {}

// Метод для разбиения запроса на слова, убирая знаки препинания и приводя к нижнему регистру
std::vector<std::string> RequestHandler::splitRequestIntoWords(const std::string& request) const {
    std::istringstream stream(request);
    std::string word;
    std::vector<std::string> words;

    if (request.empty()) {
        return words; // Возвращаем пустой вектор, если запрос пуст
    }

    while (stream >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return std::ispunct(c);  // Убираем знаки препинания
            }), word.end());
        words.push_back(toLower(word));  // Приводим к нижнему регистру
    }

    return words;
}

// Метод для приведения строки к нижнему регистру
std::string RequestHandler::toLower(const std::string& input) const {
    std::string result;
    for (char c : input) {
        result += std::tolower(c);
    }
    return result;
}

// Метод для обработки запроса и поиска документов
std::vector<std::string> RequestHandler::processRequest(const std::string& request) {
    std::vector<std::string> queryWords = splitRequestIntoWords(request);
    std::set<std::string> uniqueDocuments;

    if (queryWords.empty()) {
        std::cout << "The search query is empty.\n";
        return {};
    }

    // Поиск по каждому слову в запросе
    for (const std::string& word : queryWords) {
        std::vector<std::string> results = indexer.search(word);
        uniqueDocuments.insert(results.begin(), results.end());
    }

    // Переводим результат в вектор
    std::vector<std::string> finalResults(uniqueDocuments.begin(), uniqueDocuments.end());

    // Печать результатов
    if (finalResults.empty()) {
        std::cout << "No documents found.\n";
    }
    else {
        std::cout << "Found documents: ";
        for (const std::string& doc : finalResults) {
            std::cout << doc << " ";
        }
        std::cout << "\n";
    }

    return finalResults;
}

// Метод для сохранения результатов в JSON
void RequestHandler::saveResultsToJson(const std::vector<std::string>& results, const std::string& outputFile) {
    json output;
    output["results"] = json::array();

    // Добавление всех результатов
    for (const std::string& doc : results) {
        output["results"].push_back({ {"document", doc} });
    }

    output["total_results"] = results.size();
    output["timestamp"] = std::time(nullptr);  // Добавление временной метки

    // Запись в файл
    std::ofstream outFile(outputFile);
    if (outFile.is_open()) {
        outFile << output.dump(4);  // Красивый вывод с отступами
    }
    else {
        std::cerr << "Error opening file for writing: " << outputFile << std::endl;
    }
}
