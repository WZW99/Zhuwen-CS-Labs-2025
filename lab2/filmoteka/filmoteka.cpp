
#include "filmoteka.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <limits>

namespace {
    const size_t INITIAL_CAPACITY = 10;
    const size_t MAX_INPUT_LENGTH = 256;

    void PrintMenu() {
        std::cout << "\n=== Film Database ===\n"
                  << "1. Show all films\n"
                  << "2. Add film\n"
                  << "3. Remove film\n"
                  << "4. Update film\n"
                  << "5. Sort films by year\n"
                  << "6. Save to file\n"
                  << "7. Exit\n"
                  << "Select option: ";
    }

    void InputString(const char* prompt, char* buffer, size_t maxLength) {
        std::cout << prompt;
        std::cin.getline(buffer, maxLength);
    }
}


void Film::copyString(char*& dest, const char* source) {
    dest = new char[strlen(source) + 1];
    strcpy(dest, source);
}

Film::Film() : title(nullptr), year(0), rating(0.0f), genre(nullptr) {}

Film::Film(const char* title, int year, float rating, const char* genre) {
    copyString(this->title, title);
    this->year = year;
    this->rating = rating;
    copyString(this->genre, genre);
}

Film::Film(const Film& other) {
    copyString(title, other.title);
    year = other.year;
    rating = other.rating;
    copyString(genre, other.genre);
}

Film& Film::operator=(const Film& other) {
    if (this != &other) {
        delete[] title;
        delete[] genre;
        copyString(title, other.title);
        copyString(genre, other.genre);
        year = other.year;
        rating = other.rating;
    }
    return *this;
}

Film::~Film() {
    delete[] title;
    delete[] genre;
}

void Film::SetTitle(const char* title) {
    delete[] this->title;
    copyString(this->title, title);
}

void Film::SetYear(int year) { this->year = year; }
void Film::SetRating(float rating) { this->rating = rating; }
void Film::SetGenre(const char* genre) {
    delete[] this->genre;
    copyString(this->genre, genre);
}

const char* Film::GetTitle() const { return title; }
int Film::GetYear() const { return year; }
float Film::GetRating() const { return rating; }
const char* Film::GetGenre() const { return genre; }


namespace FilmApp {
    void InitializeList(FilmList& list) {
        list.films = new Film[INITIAL_CAPACITY];
        list.size = 0;
        list.capacity = INITIAL_CAPACITY;
    }

    void FreeList(FilmList& list) {
        delete[] list.films;
        list.films = nullptr;
        list.size = list.capacity = 0;
    }

    void ResizeList(FilmList& list) {
        size_t newCapacity = list.capacity * 2;
        Film* newFilms = new Film[newCapacity];

        for (size_t i = 0; i < list.size; ++i) {
            newFilms[i] = list.films[i];
        }

        delete[] list.films;
        list.films = newFilms;
        list.capacity = newCapacity;
    }

    void AddFilm(FilmList& list, const Film& film) {
        if (list.size >= list.capacity) {
            ResizeList(list);
        }
        list.films[list.size++] = film;
    }

    void RemoveFilm(FilmList& list, const char* title) {
        for (size_t i = 0; i < list.size; ++i) {
            if (strcmp(list.films[i].GetTitle(), title) == 0) {
                for (size_t j = i; j < list.size - 1; ++j) {
                    list.films[j] = list.films[j + 1];
                }
                list.size--;
                std::cout << "Film removed successfully.\n";
                return;
            }
        }
        std::cout << "Film not found!\n";
    }

    void UpdateFilm(FilmList& list, const char* title) {
        for (size_t i = 0; i < list.size; ++i) {
            if (strcmp(list.films[i].GetTitle(), title) == 0) {
                char buffer[MAX_INPUT_LENGTH];
                int year;
                float rating;

                InputString("New title: ", buffer, MAX_INPUT_LENGTH);
                list.films[i].SetTitle(buffer);

                std::cout << "New year: ";
                std::cin >> year;
                list.films[i].SetYear(year);

                std::cout << "New rating: ";
                std::cin >> rating;
                list.films[i].SetRating(rating);

                std::cin.ignore();
                InputString("New genre: ", buffer, MAX_INPUT_LENGTH);
                list.films[i].SetGenre(buffer);

                std::cout << "Film updated successfully.\n";
                return;
            }
        }
        std::cout << "Film not found!\n";
    }

    void PrintAll(const FilmList& list) {
        if (list.size == 0) {
            std::cout << "No films in database.\n";
            return;
        }

        for (size_t i = 0; i < list.size; ++i) {
            std::cout << "\nFilm #" << i + 1 << ":\n"
                      << "Title: " << list.films[i].GetTitle() << "\n"
                      << "Year: " << list.films[i].GetYear() << "\n"
                      << "Rating: " << list.films[i].GetRating() << "\n"
                      << "Genre: " << list.films[i].GetGenre() << "\n";
        }
    }

    void SaveToFile(const FilmList& list, const char* filename) {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for writing!\n";
            return;
        }

        file << list.size << "\n";
        for (size_t i = 0; i < list.size; ++i) {
            file << list.films[i].GetTitle() << "\n"
                 << list.films[i].GetYear() << " "
                 << list.films[i].GetRating() << "\n"
                 << list.films[i].GetGenre() << "\n";
        }

        std::cout << "Data saved to file successfully.\n";
    }

    void LoadFromFile(FilmList& list, const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for reading!\n";
            return;
        }

        size_t count;
        file >> count;
        file.ignore();

        char title[MAX_INPUT_LENGTH];
        char genre[MAX_INPUT_LENGTH];
        int year;
        float rating;

        for (size_t i = 0; i < count; ++i) {
            file.getline(title, MAX_INPUT_LENGTH);
            file >> year >> rating;
            file.ignore();
            file.getline(genre, MAX_INPUT_LENGTH);

            AddFilm(list, Film(title, year, rating, genre));
        }

        std::cout << "Data loaded from file successfully.\n";
    }

    void SortByYear(FilmList& list) {
        for (size_t i = 0; i < list.size - 1; ++i) {
            for (size_t j = 0; j < list.size - i - 1; ++j) {
                if (list.films[j].GetYear() > list.films[j + 1].GetYear()) {
                    Film temp = list.films[j];
                    list.films[j] = list.films[j + 1];
                    list.films[j + 1] = temp;
                }
            }
        }
        std::cout << "Films sorted by year.\n";
    }


    void RunApplication() {
        FilmList list;
        InitializeList(list);
        LoadFromFile(list, "/home/zhuwen/Zhuwen-CS-Labs-2025/lab2/filmoteka/films.txt");

        bool running = true;
        while (running) {
            PrintMenu();

            int choice = 0;
            while (true) {
                std::cin >> choice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a number 1-7: ";
                    continue;
                }
                if (choice < 1 || choice > 7) {
                    std::cout << "Invalid choice. Please enter 1-7: ";
                    continue;
                }
                break;
            }
            std::cin.ignore();

        switch (static_cast<MenuOptionFilms>(choice)) {
            case MenuOptionFilms::PrintFilms:
                PrintAll(list);
                break;

            case MenuOptionFilms::AddFilm: {
                char title[MAX_INPUT_LENGTH];
                char genre[MAX_INPUT_LENGTH];
                int year;
                float rating;

                InputString("Enter film title: ", title, MAX_INPUT_LENGTH);


                while (true) {
                    std::cout << "Enter release year: ";
                    std::cin >> year;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid year! ";
                        continue;
                    }
                    break;
                }


                while (true) {
                    std::cout << "Enter rating (0.0-10.0): ";
                    std::cin >> rating;
                    if (std::cin.fail() || rating < 0 || rating > 10) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid rating! ";
                        continue;
                    }
                    break;
                }
                std::cin.ignore();
                InputString("Enter genre: ", genre, MAX_INPUT_LENGTH);

                AddFilm(list, Film(title, year, rating, genre));
                std::cout << "Film added successfully.\n";
                break;
            }

                case MenuOptionFilms::RemoveFilm: {
                    char title[MAX_INPUT_LENGTH];
                    InputString("Enter film title to remove: ", title, MAX_INPUT_LENGTH);
                    RemoveFilm(list, title);
                    break;
                }

                case MenuOptionFilms::UpdateFilm: {
                    char title[MAX_INPUT_LENGTH];
                    InputString("Enter film title to update: ", title, MAX_INPUT_LENGTH);
                    UpdateFilm(list, title);
                    break;
                }

                case MenuOptionFilms::SortFilms:
                    SortByYear(list);
                    break;

                case MenuOptionFilms::SaveToFile:
                    SaveToFile(list, "/home/zhuwen/Zhuwen-CS-Labs-2025/lab2/filmoteka/films.txt");
                    break;

                case MenuOptionFilms::Exit:
                    running = 0;
                    SaveToFile(list, "/home/zhuwen/Zhuwen-CS-Labs-2025/lab2/filmoteka/films.txt");
                    std::cout << "Exiting...\n";
                    break;
                default: {
                    std::cout << "Option is not available, please enter a number between 1 and 7!\n";
                    break;
                }
            }
        }

        FreeList(list);
    }
}
