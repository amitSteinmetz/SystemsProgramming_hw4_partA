#include "Ninja.hpp"

Ninja::Ninja(std::string new_name, Point new_location, int hit_points, int new_speed) 
: Character(new_name, new_location, hit_points), speed(new_speed)
{}
void Ninja::move(const Character* enemy)
{
    return;
}
void Ninja::slash(Character* enemy)
{
    return;
}
int Ninja::getSpeed() const
{
    return 1;
}