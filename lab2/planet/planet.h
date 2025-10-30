#pragma once
#include <cstddef>
#include <cstring>

enum class MenuOption : int {
    PrintPlanets = 1,
    AddPlanet,
    RemovePlanet,
    UpdatePlanet,
    SortPlanets,
    SaveToFile,
    Exit,
};

class Planet {
 private:
    char* name{};
    int diameter{};
    bool hasLife{};
    int numberOfSatellites{};

 public:
    Planet() = default;
    Planet(char* name, int diameter, bool hasLife, int numberOfSatellites) {
        this->name = name;
        this->diameter = diameter;
        this->hasLife = hasLife;
        this->numberOfSatellites = numberOfSatellites;
    }

    Planet(const Planet& source) {
        this->name = new char[std::strlen(source.name) + 1];
        std::strncpy(this->name, source.name, std::strlen(source.name) + 1);
        this->diameter = source.diameter;
        this->hasLife = source.hasLife;
        this->numberOfSatellites = source.numberOfSatellites;
    }

    Planet& operator=(const Planet& source) {
        if (this != &source) {
            delete[] name;
        }
        this->name = new char[std::strlen(source.name) + 1];
        std::strncpy(this->name, source.name, std::strlen(source.name) + 1);
        this->diameter = source.diameter;
        this->hasLife = source.hasLife;
        this->numberOfSatellites = source.numberOfSatellites;
        return *this;
    }

    void SetName(const char* newName) {
        if (name != nullptr) {
            delete[] name;
        }
        name = new char[std::strlen(newName) + 1];
        std::strncpy(name, newName, std::strlen(newName) + 1);
    }
    void SetDiameter(int diameter) { this->diameter = diameter; }
    void SetHasLife(bool hasLife) { this->hasLife = hasLife; }
    void SetNumberOfSatellites(int numberOfSatellites) { this->numberOfSatellites = numberOfSatellites; }

    char* GetName() { return name; }
    int GetDiameter() { return diameter; }
    bool HasLife() { return hasLife; }
    int GetNumberOfSatellites() { return numberOfSatellites; }

    ~Planet() {
        if (this->name != nullptr) {
            delete[] this->name;
            this->name = nullptr;
        }
    }
};

struct PlanetList {
    Planet* planets{};
    size_t size{};
};

namespace planetApp {
PlanetList CreatePlanetList();
void DeletePlanetList(PlanetList& list);

void LoadDataFromFile(PlanetList& list, const char* fileName);
void SaveDataToFile(PlanetList& list, const char* fileName);

void ExpandPlanetList(PlanetList& list);
void ShrinkPlanetList(PlanetList& list, char* planetName);

void AddPlanetToList(PlanetList& list, Planet& newPlanet);
void RemovePlanetFromList(PlanetList& list);

void PrintPlanetList(PlanetList& list);

size_t FindPlanetIndexByName(PlanetList& list, char* planetName);

void HandleMenuSelection(PlanetList& list, char& continueExecution);
void StartApplication();
}
