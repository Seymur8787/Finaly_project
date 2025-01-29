#include "indexer.h"

// Преобразование строки в нижний регистр
std::string Indexer::toLower(const std::string& input) const {
    std::string result;
    for (char c : input) {
        result += std::tolower(c);
    }
    return result;
}

// Метод для добавления документа в индекс
void Indexer::addDocument(const std::string& docName, const std::string& content) {
    // Индексируем документ
    indexDocument(docName, content);

    // Сохраняем документ в список
    documents[docName] = content;
}

// Метод для индексации документа
void Indexer::indexDocument(const std::string& docName, const std::string& content) {
    std::string lowerContent = toLower(content);
    std::istringstream stream(lowerContent);
    std::string word;

    while (stream >> word) {
        index[word].insert(docName);
    }
}

// Метод для поиска по слову с релевантностью
std::vector<std::pair<std::string, int>> Indexer::searchWithRelevance(const std::string& word) const {
    std::vector<std::pair<std::string, int>> results;
    auto it = index.find(word);

    if (it != index.end()) {
        for (const auto& doc : it->second) {
            int count = std::count(it->second.begin(), it->second.end(), doc);
            results.push_back({ doc, count });
        }
    }

    return results;
}

// Метод для поиска по слову
std::vector<std::string> Indexer::search(const std::string& word) const {
    std::vector<std::string> results;
    auto it = index.find(word);

    if (it != index.end()) {
        results.assign(it->second.begin(), it->second.end());
    }

    return results;
}

// Метод для автодополнения слов (по префиксу)
std::vector<std::string> Indexer::autoComplete(const std::string& prefix) const {
    std::vector<std::string> suggestions;
    for (const auto& [word, docs] : index) {
        if (word.find(prefix) == 0) {  // Проверка, начинается ли слово с префикса
            suggestions.push_back(word);
        }
    }
    return suggestions;
}

// Метод для сохранения индекса в файл
void Indexer::saveIndexToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& [word, docs] : index) {
            outFile << word << ": ";
            for (const auto& doc : docs) {
                outFile << doc << " ";
            }
            outFile << "\n";
        }
    }
    else {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
    }
}

// Метод для загрузки индекса из файла
void Indexer::loadIndexFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream stream(line);
            std::string word;
            stream >> word;
            std::unordered_set<std::string> docs;
            std::string doc;
            while (stream >> doc) {
                docs.insert(doc);
            }
            index[word] = docs;
        }
    }
    else {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
    }
}
