#ifndef INDEXER_H
#define INDEXER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

class IndexerTest;

class Indexer {
public:
    // Метод для добавления документа в индекс
    void addDocument(const std::string& docName, const std::string& content);

    // Метод для индексации документов
    void indexDocument(const std::string& docName, const std::string& content);

    friend class IndexerTest;

    // Метод для поиска по слову с релевантностью (счётчик вхождений)
    std::vector<std::pair<std::string, int>> searchWithRelevance(const std::string& word) const;

    // Метод для поиска по слову
    std::vector<std::string> search(const std::string& word) const;

    // Метод для автодополнения слов
    std::vector<std::string> autoComplete(const std::string& prefix) const;

    // Метод для сохранения индекса в файл
    void saveIndexToFile(const std::string& filename) const;

    // Метод для загрузки индекса из файла
    void loadIndexFromFile(const std::string& filename);

private:
    // Индекс, где ключ - слово, а значение - множество файлов, в которых оно встречается
    std::unordered_map<std::string, std::unordered_set<std::string>> index;

    // Список документов, где ключ - название документа, а значение - его содержимое
    std::unordered_map<std::string, std::string> documents;

    // Преобразование строки в нижний регистр
    std::string toLower(const std::string& input) const;
};

#endif // INDEXER_H
