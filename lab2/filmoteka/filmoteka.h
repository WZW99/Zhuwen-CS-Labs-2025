#pragma once
#include <cstddef>

enum class MenuOptionFilms : int {
    PrintFilms = 1,
    AddFilm,
    RemoveFilm,
    UpdateFilm,
    SortFilms,
    SaveToFile,
    Exit
};

class Film {
private:
    char* title;
    int year;
    float rating;
    char* genre;

    void copyString(char*& dest, const char* source);

public:
    Film();
    Film(const char* title, int year, float rating, const char* genre);
    Film(const Film& other);
    Film& operator=(const Film& other);
    ~Film();

    void SetTitle(const char* title);
    void SetYear(int year);
    void SetRating(float rating);
    void SetGenre(const char* genre);

    const char* GetTitle() const;
    int GetYear() const;
    float GetRating() const;
    const char* GetGenre() const;
};

struct FilmList {
    Film* films;
    size_t size;
    size_t capacity;
};

namespace FilmApp {
    void InitializeList(FilmList& list);
    void FreeList(FilmList& list);
    void AddFilm(FilmList& list, const Film& film);
    void RemoveFilm(FilmList& list, const char* title);
    void UpdateFilm(FilmList& list, const char* title);
    void PrintAll(const FilmList& list);
    void SaveToFile(const FilmList& list, const char* filename);
    void LoadFromFile(FilmList& list, const char* filename);
    void SortByYear(FilmList& list);
    void RunApplication();
}
