#pragma once
#include "Character.hpp"

class Cowboy : public Character
{
    // Attributes:
    int bullets_amount;

    // Ctors:
    public:
    Cowboy(std::string new_name, Point new_location);
    
    // Methods:
    void shoot(Character* enemy);
    bool hasBullets() const;
    void reload();
    int getBulletsAmount() const;

};