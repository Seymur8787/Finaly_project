#include "gtest/gtest.h"
#include "Indexer.h"  // Включаем ваш исходный файл

class IndexerTest : public ::testing::Test {
protected:
    Indexer indexer;

    void SetUp() override {
        // Здесь можно инициализировать данные для каждого теста
    }

    void TearDown() override {
        // Очистка данных после тестов (если нужно)
    }
};

// Тест для метода addDocument
TEST_F(IndexerTest, AddDocumentTest) {
    indexer.addDocument("doc1", "This is a test document");

    // Проверяем, что документ был добавлен в индекс
    auto result = indexer.search("test");
    ASSERT_EQ(result.size(), 1);  // Ожидаем один документ
    EXPECT_EQ(result[0], "doc1");  // Документ должен быть "doc1"
}

// Тест для метода searchWithRelevance
TEST_F(IndexerTest, SearchWithRelevanceTest) {
    indexer.addDocument("doc1", "This is a test document");

    // Проверяем поиск с релевантностью
    auto result = indexer.searchWithRelevance("test");
    ASSERT_EQ(result.size(), 1);  // Ожидаем один результат
    EXPECT_EQ(result[0].first, "doc1");  // Документ должен быть "doc1"
    EXPECT_EQ(result[0].second, 1);  // Релевантность должна быть равна 1
}

// Тест для метода autoComplete
TEST_F(IndexerTest, AutoCompleteTest) {
    indexer.addDocument("doc1", "This is a test document");

    // Проверяем автодополнение
    auto result = indexer.autoComplete("te");
    ASSERT_EQ(result.size(), 1);  // Ожидаем один результат
    EXPECT_EQ(result[0], "test");  // Ожидаем слово "test"
}

// Тест для метода saveIndexToFile и loadIndexFromFile
TEST_F(IndexerTest, SaveAndLoadIndexTest) {
    indexer.addDocument("doc1", "This is a test document");

    // Сохраняем индекс в файл
    indexer.saveIndexToFile("test_index.txt");

    // Создаем новый объект и загружаем индекс из файла
    Indexer newIndexer;
    newIndexer.loadIndexFromFile("test_index.txt");

    // Проверяем, что данные были правильно загружены
    auto result = newIndexer.search("test");
    ASSERT_EQ(result.size(), 1);  // Ожидаем один результат
    EXPECT_EQ(result[0], "doc1");  // Документ должен быть "doc1"
}
