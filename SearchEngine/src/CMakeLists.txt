# Указываем файлы исходного кода
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Создаём библиотеку
add_library(SearchEngineLib ${SOURCES})

# Указываем пути к заголовочным файлам
target_include_directories(SearchEngineLib PUBLIC
    ${CMAKE_SOURCE_DIR}/SearchEngine/includes
    ${json_SOURCE_DIR}/single_include  # Подключаем JSON
)

# Создаём исполняемый файл
add_executable(SearchEngine main.cpp)

# Связываем исполняемый файл с библиотекой
target_link_libraries(SearchEngine PRIVATE SearchEngineLib)
