#include "Document.h"
#include <sstream>
#include <algorithm>

// Конструктор
Document::Document(int id, const std::string& content)
    : id(id), content(content), relevance(0.0) {
}

// Геттер для ID документа
int Document::getId() const {
    return id;
}

// Геттер для содержимого документа
const std::string& Document::getContent() const {
    return content;
}

// Метод для обновления содержимого документа
void Document::setContent(const std::string& newContent) {
    content = newContent;
}

// Геттер для релевантности
double Document::getRelevance() const {
    return relevance;
}

// Метод для установки релевантности
void Document::setRelevance(double newRelevance) {
    relevance = newRelevance;
}

// Метод для подсчета вхождений слова в документ
int Document::countOccurrences(const std::string& word) const {
    std::istringstream stream(content);
    std::string currentWord;
    int count = 0;
    while (stream >> currentWord) {
        if (currentWord == word) {
            count++;
        }
    }
    return count;
}
