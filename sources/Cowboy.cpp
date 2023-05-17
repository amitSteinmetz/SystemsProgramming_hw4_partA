#include "Cowboy.hpp"

// Ctors:
Cowboy::Cowboy(std::string new_name, Point new_location)
  : Character(new_name, new_location, 110) ,bullets_amount(6)
{}

// Methods:
void Cowboy::shoot(Character* enemy)
{
    return;
}
bool Cowboy::hasBullets() const
{
    return true;
}
void Cowboy::reload()
{
    return;
}
int Cowboy::getBulletsAmount() const
{
    return bullets_amount;
}