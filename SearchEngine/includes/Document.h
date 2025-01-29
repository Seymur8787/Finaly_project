#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include <unordered_map>

class Document {
public:
    // Конструктор
    Document(int id, const std::string& content);

    // Геттер для ID документа
    int getId() const;

    // Геттер для содержимого документа
    const std::string& getContent() const;

    // Метод для обновления содержимого документа
    void setContent(const std::string& newContent);

    // Геттер для релевантности
    double getRelevance() const;

    // Метод для установки релевантности
    void setRelevance(double newRelevance);

    // Метод для подсчета вхождений слова в документ
    int countOccurrences(const std::string& word) const;

private:
    int id;                 // Идентификатор документа
    std::string content;    // Содержимое документа
    double relevance;       // Релевантность документа
};

#endif // DOCUMENT_H
