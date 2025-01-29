# Указываем исходные файлы для тестов
set(TEST_SOURCES MyTest.cpp)

# Создаём исполняемый файл для тестов
add_executable(SearchEngineTests ${TEST_SOURCES})

# Указываем пути к заголовочным файлам
target_include_directories(SearchEngineTests PRIVATE
    ${CMAKE_SOURCE_DIR}/SearchEngine/includes
    ${json_SOURCE_DIR}/single_include  # Подключаем JSON
)

# Подключаем библиотеки GoogleTest и SearchEngineLib
target_link_libraries(SearchEngineTests PRIVATE gtest gtest_main SearchEngineLib)

# Добавляем тесты
add_test(NAME SearchEngineTests COMMAND SearchEngineTests)
