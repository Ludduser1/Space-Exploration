#ifndef PLANET_HPP
#define PLANET_HPP

#include <string>

struct Planet {
    std::string name;
    std::string description;
    std::string dangerDescription;
    std::string item;

    int fuelCost;
    int dangerLevel; //1-5
};

#endif