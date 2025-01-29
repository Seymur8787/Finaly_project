cmake_minimum_required(VERSION 3.8)

# Название проекта
project(SearchEngine VERSION 1.0 LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем FetchContent
include(FetchContent)

# Подключаем GoogleTest через FetchContent
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Подключаем JSON for Modern C++
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# Добавляем поддиректории
add_subdirectory(src)
add_subdirectory(tests)

# Включаем тестирование
enable_testing()
