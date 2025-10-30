cmake_minimum_required(VERSION 3.20)
project(lab_6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(${PROJECT_NAME} Main.cpp)

# Подключаем модуль polynomial
add_subdirectory(Polynomial)

# Настройки компиляции
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Werror
    -pedantic
)

# Связывание с библиотекой polynomial
target_link_libraries(${PROJECT_NAME} Polynomial)
