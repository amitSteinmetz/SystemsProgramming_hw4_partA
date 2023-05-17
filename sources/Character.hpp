#pragma once
#include "Point.hpp"
#include <string>
#include <iostream>

class Character
{
    // Attributes:
    Point location;
    std::string name;
    int hit_points;  

    // Ctors:
    public:
    Character(std::string new_name, Point new_location, int hit_points);

    // Methods:
    bool isAlive();
    double distance(Character* other) const;
    void hit(int hit_points);
    std::string getName() const;
    Point getLocation() const;
    int getHitPoints() const;
    void setHitPoints(int points_to_subtract);
    std::string print() const;
    friend std::ostream& operator<<(std::ostream& ost, std::string character_details);
};
