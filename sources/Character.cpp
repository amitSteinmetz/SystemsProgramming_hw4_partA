#include "Character.hpp"
using namespace std;

Character::Character(std::string new_name, Point new_location, int hit_points)
: name(new_name), location(new_location)
{}

bool Character::isAlive()
{
    return true;
}
double Character::distance(const Character* other) const
{
    return 1;
}
void Character::hit(int hit_points)
{
    return;
}
std::string Character::getName() const
{
    return NULL;
}
Point Character::getLocation() const
{
    return Point(0,0);
}
string Character::print() const
{
    return "";
}
std::ostream& operator<<(std::ostream& ost, std::string character_details)
{
    ost << character_details;
    return ost;
}
int Character::getHitPoints() const
{
    return hit_points;
}
void Character::setHitPoints(int points_to_subtract)
{
    hit_points -= points_to_subtract;
}
