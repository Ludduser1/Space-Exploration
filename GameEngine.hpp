#ifndef GAMENEGINE_HPP
#define GAMENEGINE_HPP

#include <vector>
#include <string>
#include "Planet.hpp"

class GameEngine{
    private:
    int fuel;
    int hullHealth;
    int credits;
    std::string currentLocation;
    bool gameOn;
    
    std::vector <Planet> solarsystem;
    std::vector <std::string> backpack;

    void clear();
    void initiatePlanets();
    void showStatus();
    void modifyTravel(int choice);
    void openBackpack();
    void exchangeStation();

    public:
    GameEngine();
    void start(); //mainloop

};

#endif