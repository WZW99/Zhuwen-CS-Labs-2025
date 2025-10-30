#include "planet.h"

#include <cstring>
#include <fstream>
#include <iostream>

namespace {
const int kDefaultPlanetCount = 9;
const int kMaxPlanetNameLength = 128;

void PrintMainMenu() {
    std::cout << "\n1. Print the list of planets\n2. Add a planet\n3. Remove a planet\n4. Update a planet\n5. Sort the list of planets\n6. Save data to file\n7. Exit\n";
}

Planet InputNewPlanet() {
    Planet newPlanet{};

    char buffer[kMaxPlanetNameLength];
    std::cout << '\n' << "Enter the name of the new planet: ";
    std::cin >> buffer;

    newPlanet.SetName(buffer);

    int diameter = 0;
    std::cout << "Enter the diameter of the new planet: ";
    std::cin >> diameter;
    newPlanet.SetDiameter(diameter);

    bool hasLife = 0;
    std::cout << "Is there life on the planet? (0/1): ";
    std::cin >> hasLife;
    newPlanet.SetHasLife(hasLife);

    int numberOfSatellites = 0;
    std::cout << "Enter the number of satellites of the new planet: ";
    std::cin >> numberOfSatellites;
    newPlanet.SetNumberOfSatellites(numberOfSatellites);

    return newPlanet;
}
}

namespace planetApp {

PlanetList CreatePlanetList() {
    PlanetList list{};
    list.planets = new Planet[kDefaultPlanetCount];
    list.size = kDefaultPlanetCount;
    return list;
}

bool IsPlanetListEmpty(const PlanetList& list, const char* actionMessage = nullptr) {
    if (list.size == 0) {
        std::cout << "Planet list is empty.";
        if (actionMessage != nullptr && std::strlen(actionMessage) > 0) {
            std::cout << " " << actionMessage;
        }
        std::cout << '\n';
        return true;
    }
    return false;
}

void LoadDataFromFile(PlanetList& list, const char* fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error opening file!\n";
        return;
    }

    file >> list.size;
    char buffer[kMaxPlanetNameLength];
    int diameter{};
    bool hasLife{};
    int numberOfSatellites{};
    for (size_t i = 0; i < list.size; ++i) {
        file >> buffer >> diameter >> hasLife >> numberOfSatellites;

        list.planets[i].SetName(buffer);
        list.planets[i].SetDiameter(diameter);
        list.planets[i].SetHasLife(hasLife);
        list.planets[i].SetNumberOfSatellites(numberOfSatellites);
    }

    file.close();
}

void SaveDataToFile(PlanetList& list, const char* fileName) {
    std::ofstream file(fileName, std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Error opening file!\n";
        return;
    }

    file << list.size << '\n';
    for (size_t i = 0; i < list.size; ++i) {
        file << list.planets[i].GetName() << ' ' << list.planets[i].GetDiameter() << ' ' << list.planets[i].HasLife() << ' ' << list.planets[i].GetNumberOfSatellites()
             << '\n';
    }

    file.close();
}

void ExpandPlanetList(PlanetList& list) {
    size_t newListSize = list.size + 1;
    Planet* newPlanets = new Planet[newListSize];
    for (size_t i = 0; i < list.size; ++i) {
        newPlanets[i] = list.planets[i];
    }

    Planet* oldPlanets = list.planets;
    list.planets = newPlanets;


    delete[] oldPlanets;

    list.size = newListSize;
    std::cout << "Planet added!\n";
}

void AddPlanetToList(PlanetList& list, Planet& newPlanet) {
    ExpandPlanetList(list);
    list.planets[list.size - 1] = newPlanet;
}

size_t FindPlanetIndexByName(PlanetList& list, char* planetName) {
    for (size_t i = 0; i < list.size; ++i) {
        if (*list.planets[i].GetName() == *planetName) {
            return i;
        }
    }
    std::cout << "Planet with the name " << planetName << " not found\n";
    return -1;
}
void ShrinkPlanetList(PlanetList& list, char* planetName) {
    size_t indexToRemove = FindPlanetIndexByName(list, planetName);
    if (indexToRemove == -1) return;

    size_t newListSize = list.size - 1;
    Planet* newPlanets = new Planet[newListSize];

    for (size_t i = 0, j = 0; i < list.size; ++i) {
        if (i != indexToRemove) {
            newPlanets[j++] = list.planets[i];
        }
    }

    delete[] list.planets;
    list.planets = newPlanets;
    list.size = newListSize;
    std::cout << "Planet removed!\n";
}

void RemovePlanetFromList(PlanetList& list) {
    if (IsPlanetListEmpty(list, "Nothing to remove.")) return;

    char buffer[kMaxPlanetNameLength];
    std::cout << "Enter the name of the planet to remove: ";
    std::cin >> buffer;

    ShrinkPlanetList(list, buffer);
}

void SortPlanetsByDiameter(PlanetList& list) {
    if(IsPlanetListEmpty(list, "Nothing to sort.")) return;
    for (size_t i = 0; i < list.size - 1; ++i) {
        for (size_t j = 0; j < list.size - i - 1; ++j) {
            if (list.planets[j].GetDiameter() > list.planets[j + 1].GetDiameter()) {
                std::swap(list.planets[j + 1],list.planets[j]);

            }
        }
    }
}

void UpdatePlanetInList(PlanetList& list) {
    if(IsPlanetListEmpty(list, "Nothing to update.")) return;
    std::cout << "Enter the name of the planet you want to update: ";
    char buffer[kMaxPlanetNameLength];
    std::cin >> buffer;

    size_t planetIndex = FindPlanetIndexByName(list, buffer);
    if (planetIndex == -1) {
        return;
    } else {
        list.planets[planetIndex] = InputNewPlanet();
    }
}

void DeletePlanetList(PlanetList& list) {

    delete[] list.planets;
}

void PrintPlanetList(PlanetList& list) {
    if(IsPlanetListEmpty(list)) return;
    for (size_t i = 0; i < list.size; ++i) {
        std::cout << "Name: " << list.planets[i].GetName() << '\n';
        std::cout << "Diameter: " << list.planets[i].GetDiameter() << '\n';
        std::cout << "Life: ";
        if (list.planets[i].HasLife()) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
        std::cout << "Number of Satellites: " << list.planets[i].GetNumberOfSatellites() << "\n\n";
    }
}

void HandleMenuSelection(PlanetList& list, char& continueExecution) {
    int selection = 0;
    PrintMainMenu();
    std::cout << "Select an option: ";
    std::cin >> selection;

    switch (static_cast<MenuOption>(selection)) {
        case MenuOption::PrintPlanets: {
            PrintPlanetList(list);
            break;
        }
        case MenuOption::AddPlanet: {
            Planet newPlanet = InputNewPlanet();
            AddPlanetToList(list, newPlanet);
            break;
        }
        case MenuOption::RemovePlanet: {
            RemovePlanetFromList(list);
            break;
        }
        case MenuOption::SaveToFile: {
            SaveDataToFile(list, "/home/zhuwen/Zhuwen-CS-Labs-2025/lab2/planet/planets.txt");
            break;
        }
        case MenuOption::SortPlanets: {
            SortPlanetsByDiameter(list);
            break;
        }
        case MenuOption::UpdatePlanet: {
            UpdatePlanetInList(list);
            break;
        }
        case MenuOption::Exit: {
            continueExecution = 'n';
            break;
        }
        default: {
            std::cout << "Option " << selection << " is not available, please enter a number between 1 and 7!\n";
            break;
        }
    }
}

void StartApplication() {
    char continueExecution = 'y';

    PlanetList list = CreatePlanetList();
    LoadDataFromFile(list, "/home/zhuwen/Zhuwen-CS-Labs-2025/lab2/planet/planets.txt");
    while (continueExecution == 'y') {
        HandleMenuSelection(list, continueExecution);
    }

    DeletePlanetList(list);
}
}
