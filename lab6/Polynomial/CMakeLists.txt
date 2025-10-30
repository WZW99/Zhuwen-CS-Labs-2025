cmake_minimum_required(VERSION 3.20)
project(Polynomial)

# Создаем статическую библиотеку
add_library(${PROJECT_NAME} STATIC
    Term.cpp
    Polynomial.cpp
)

# Настройки компиляции
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
