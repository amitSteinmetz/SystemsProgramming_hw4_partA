#include "Team.hpp"

class SmartTeam : public Team
{
    // Overriding methods
    std::string print();
    void attack(Team* enemies);
    int stillAlive() const;
};