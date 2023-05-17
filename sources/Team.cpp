#include "Team.hpp"

 // Ctor
Team::Team(Character* new_leader) : leader(new_leader), members()
{}

// Dtor
Team::~Team() {};

// Methods
void Team::add(const Character* new_warrior)
{
    return;
}
void Team::attack(Team* enemies)
{
    return;
}
int Team::stillAlive() const
{
    return 0;
}
std::string Team::print()
{
    return "";
}

