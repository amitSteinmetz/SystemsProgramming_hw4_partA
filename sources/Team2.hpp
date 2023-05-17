#include "Team.hpp"

class Team2 : public Team
{
    // Overriding methods
    std::string print();
    void attack(Team* enemies);
    int stillAlive() const;
};