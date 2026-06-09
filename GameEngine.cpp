#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "GameEngine.hpp"

GameEngine::GameEngine() {
    fuel = 100;
    hullHealth = 100;
    credits = 100;
    currentLocation = "Earth";
    gameOn = true;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    initiatePlanets();
}

void GameEngine::clear() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif    
}

void GameEngine::initiatePlanets() {
    solarsystem = {
        {"MERCURY", "Extreme heat on one side, ice-cold on the other.", "Solar storms", "Unique Solar Panel", 20, 3},
        {"VENUS", "an extreme greenhouse effect", "acidic rain", "heat resisant sheild", 15, 5},
        {"MARS", "The red planet", "Heavy sandstorms", "alien artifact", 15, 2},
        {"JUPITER", "The gas giant", "strong gravitaional pull", "Diamonds", 30, 5},
        {"SATURNUS", "The ringed planet", "Potential asteroidskollision", "Ice-core", 40, 4},
        {"URANUS", "Icecold gas planet", "Icestorm freezes gastank", "Methanegas-condensator", 45, 3},
        {"NEPTUNUS", "The blue planet", "Harmful supersonic winds", "Diamonds", 50, 4},
        {"PLUTO", "The smallest of the solarsystem", "Atmosphereic collapse", "Abandoned mine", 60, 3}
    };
}

void GameEngine::openBackpack() {
    std::cout << " In pack: ";
    if (backpack.empty()) {
        std::cout << "EMPTY";
    } else {
        for (const auto & thing : backpack) {
            std::cout << thing << std::endl;
        }
        
    }
}

void GameEngine::showStatus() {
    clear();
    std::cout << "==============STATUS===============" << std::endl;
    std::cout << "Location: " << currentLocation << std::endl;
    std::cout << "Fuel: " << fuel << std::endl;
    std::cout << "Ship hull: " << hullHealth << std::endl;
    std::cout << "Wallet; " << credits << std::endl;
    openBackpack();
}

void GameEngine::exchangeStation() {
    bool tradingStation = true;
    while (tradingStation) {
        std::cout << "==========TRADING STATION===========" << std::endl;
        std::cout << "Your credits: " << credits << std::endl;
        std::cout << "1. Buy fuel (+20%)" << std::endl;
        std::cout << "2. Repair hull (+25%)" << std::endl;
        std::cout << "3. Sell space-scrap (50 credits/scrap)" << std::endl;
        std::cout << "4. Leave the trading station" << std::endl;
        std::cout << "Choose between the options: " << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            if (credits >=25) {
                fuel += 20;
                credits -= 25;
                std::cout << "fueling up" << std::endl;
            } else {
                std::cout << "Not ennough credits";
            }
            std::cin.ignore(); std::cin.get();
        }
        else if (choice == 2) {
            if (credits >= 30) {
                hullHealth += 25;
                if (hullHealth > 100) {
                    hullHealth = 100;
                }
                credits -= 30;
                std::cout << "Repairing the hull" << std::endl;
            } else {
                std::cout << "Not enough credits";
            }
            std::cin.ignore(); std::cin.get();
        }
        else if (choice == 3) {
            if (!backpack.empty()) {
                std::cout << "You sold: " << backpack.back() << std::endl;
                backpack.pop_back();
                credits += 50;
            } else {
                std::cout << "Your backpack is empty" << std::endl;
            }
            std::cin.ignore(); std::cin.get();
        }
        else if (choice == 4) {
            std::cout << "Leaving trade station" << std::endl;
            tradingStation = false;
        }
    }
}

void GameEngine::modifyTravel(int choice) {
    Planet chosenPlanet = solarsystem[choice - 1];

    if (fuel < chosenPlanet.fuelCost) {
        std::cout << "not enough fuel to reach" << chosenPlanet.name << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }

    fuel -= chosenPlanet.fuelCost;
    currentLocation = chosenPlanet.name;

    clear();
    std::cout << "You reach the orbit of " << chosenPlanet.name << std::endl;
    std::cout << chosenPlanet.description << std::endl;
    std::cout << "Beware: " << chosenPlanet.dangerLevel << " Has been detected" << std::endl;

    //Safety equipment
    bool (activeProtection) = false;
    if (chosenPlanet.name == "VENUS") {
        for (const auto & userItem : backpack) {
            if (userItem == "Shield") activeProtection = true;
        }
    }

    if (activeProtection) {
        std::cout << "The protection keeps u safe" << std::endl;
    }

    std::cout << "1. Land carefult.. Cost: 10% extra fuel)" << "2. Take a chance and go" << "Your choice: ";
    
    int action;
    std::cin >> action;

    int random1 = std::rand() % 10 + 1;

    if (action == 1) {
        std::cout << "The landing was a success";
        fuel -= 10;
        std::cout << "You peform a search on the surface, and find: " << chosenPlanet.item << std::endl;
        backpack.push_back(chosenPlanet.item);
    } else {
        if (random1 < (chosenPlanet.dangerLevel * 2) && !activeProtection) {
            int damageToPlayer = chosenPlanet.dangerLevel * 15;
            hullHealth -= damageToPlayer;
            std::cout << "FAILURE. The danger hit the ship. The hull took " << damageToPlayer << "% damage";
        } else if (activeProtection) {
            std::cout << "SUCCESS. the danger is clear, but the protection works. you yield: " << chosenPlanet.item << std::endl;
            backpack.push_back(chosenPlanet.item);
        } else {
            std::cout << "INCREDIBLE SUCCESS. you evaded the danger completely and yield: " << chosenPlanet.item << std::endl;
            backpack.push_back(chosenPlanet.item);
        }
    }

    if (backpack.size() >= 4 && hullHealth > 0) {
        std::cout << "You managed to gather enough materials to advance research on earth" << std::endl;
        std::cout << "Thank you for you contribution" << " THE END" << std::endl;
        gameOn = false;
    } else if (hullHealth <= 0) {
        std::cout << "Shiphull destroyed.. game over" << std::endl;
        gameOn = false;
    } else {
        std::cout << "Press enter to continue exploration of the solarsystem" << std::endl;
        std::cin.ignore(); std::cin.get();
    }

}

void GameEngine::start() {
    clear();
    std::cout << "=================MISSION=================" << std::endl; 
    std::cout << "Your misson: gather 4 items from the"
    << " solarsystem to progress the research on earth" << std::endl;
    std::cout << "Earn credits to further your exploration" << std::endl;
    std::cin.get();

    while (gameOn) {
        showStatus();
        std::cout << "Where to set course? " << std::endl;
        for (size_t i = 0; i < solarsystem.size(); ++i) {
            std::cout << i + 1 << ". " << solarsystem[i].name
            << " Fuel" << solarsystem[i].fuelCost << "%" << " Risk: " << solarsystem[i].dangerLevel;
        }
        std::cout << "10. Go to trading system" << std::endl;
        std::cout << "9. Abort mission" << std::endl;
        
        int choice;
        std::cin >> choice;

        if (choice == 9) {
    std::cout << "Mission aborted" << std::endl;
    gameOn = false;
    } else if (choice == 10) { // <-- LÖSNINGEN: Skriv "else if" här!
    if (currentLocation == "earth") {
        exchangeStation();
    } else {
        std::cout << "U need to be in earths orbit to buy" << std::endl;
        std::cin.ignore(); std::cin.get();
    }
    } else if (choice > 0 && choice <= static_cast<int>(solarsystem.size())) {
    modifyTravel(choice);
    } 
    else {
    std::cout << "Invalid course" << std::endl;
    std::cin.ignore(); std::cin.get();
    }

    }
    std::cout << "Goodbye" << std::endl;
    }

