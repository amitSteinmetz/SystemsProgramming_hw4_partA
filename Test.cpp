#include "doctest.h"
#include "sources/Point.hpp"
#include "sources/Character.hpp"
#include "sources/Cowboy.hpp"
#include "sources/YoungNinja.hpp"
#include "sources/TrainedNinja.hpp"
#include "sources/OldNinja.hpp"
#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include "sources/SmartTeam.hpp"

/* Point class */ 

TEST_CASE("Same points as parameters to moveTowards()")
{
    Point a(1,2);
    Point res = Point::moveTowards(a,a,2);

    CHECK_EQ(res.getX(), a.getX());
    CHECK_EQ(res.getY(), a.getY());
}

TEST_CASE("Distance parameter in moveTowards() is zero")
{
    Point a(1,2), b(3,4);
    Point res1 = Point::moveTowards(a,b,0);
    Point res2 = Point::moveTowards(a,a,0);

    // In all cases, return point should be same to source point
    CHECK_EQ(res1.getX(), a.getX());
    CHECK_EQ(res1.getY(), a.getY());
    CHECK_EQ(res2.getX(), a.getX());
    CHECK_EQ(res2.getY(), a.getY());
}

TEST_CASE("Distance parameter in moveTowards() should be non negative")
{
    Point a(1,2), b(3,4);

    CHECK_THROWS(Point::moveTowards(a,b,-1));
}

/* Character class */

TEST_CASE("is_alive() return values")
{
    Point a(1,2), b(3,4);
    Character c1("Amit1", a, 0); // hit_points equal to 0 
    Character c2("Amit2", b, 10); 

    CHECK_FALSE(c1.isAlive());
    CHECK(c2.isAlive() == true);
}

TEST_CASE("Same character as parameters to distance()")
{
    Point a(1,2);
    Character c1("Amit1", a, 0); 
    Character c2("Amit2", a, 0);   
    
    CHECK(c1.distance(&c1) == 0);
    CHECK(c1.distance(&c2) != 0); // Two different characters can't be at same location 
    CHECK_GT(c1.distance(&c2), 0); // Distance is always non-negative
}

TEST_CASE("Correct amount of hit points for characters")
{
    Point a(1,2), b(25,35), c(25.5, 35.5), d(22,32);
    YoungNinja *jayson = new YoungNinja("Jayson", a);
    TrainedNinja *jimmy = new TrainedNinja("Jimmy", b);
    OldNinja *lebron = new OldNinja("Lebron", c);
    Cowboy *nicola = new Cowboy("Nicola", d);

    CHECK(jayson->getHitPoints() == 100);
    CHECK(jimmy->getHitPoints() == 120);
    CHECK(lebron->getHitPoints() == 150);
    CHECK(nicola->getHitPoints() == 110);
}

TEST_CASE("Correct amount of bullets for characters")
{
    Point a(1,2);
    Cowboy *nicola = new Cowboy("Nicola", a);

    CHECK(nicola->getBulletsAmount() == 6);
}

TEST_CASE("hit() edge cases")
{
    Point a(1,2);
    Cowboy *tom = new Cowboy("Tom", a);
    int test_hitPoints = tom->getHitPoints();

    tom->hit(0); // Zero points to subtract, should have no effect

    CHECK(test_hitPoints == 110);
    CHECK_THROWS(tom->hit(-1)); // hit() can't get a negative number as parameter

    tom->hit(120); // More points to subtract than initalized cowboy has (110), so all hit_points that the cowboy has subtracted

    CHECK(tom->getHitPoints() == 0); 
}

TEST_CASE("shoot() effect and edge cases")
{
    Point a(1,2), b(3,4), c(5,6);
    Cowboy *tom = new Cowboy("Tom", a); // Initalized cowboy has 110 hit_points
    Cowboy *jerry = new Cowboy("Jerry", b); 
    Cowboy *johnDoe = new Cowboy("JohnDoe", c); 

    for (int i = 0; i < 6; ++i) jerry->shoot(tom); // Tom lost 60 hit_points
    CHECK(tom->getHitPoints() == 50);
    CHECK(jerry->getBulletsAmount() == 0); // Initalized cowboy has 6 bullets, jerry used all of them. 

    jerry->shoot(tom); 
    CHECK(tom->getHitPoints() == 50); // No effect to an unarmed man shot

    tom->hit(50); // Now tom has 0 hit_points == Dead
    tom->shoot(jerry); 
    CHECK(jerry->getHitPoints() == 110); // No effect to a dead man shot

    johnDoe->shoot(tom);
    CHECK(tom->getHitPoints() == 0); // No effect to shot against a dead man
}

TEST_CASE("hasBullets() return values")
{
    Point a(1,2), b(3,4);
    Cowboy *tom = new Cowboy("Tom", a); // Initalized cowboy has 6 bullets
    Cowboy *jerry = new Cowboy("Jerry", b); 

    CHECK(tom->hasBullets() == true);

    for (int i = 0; i < 6; ++i) tom->shoot(jerry); // Tom waisted his bullets
    CHECK_FALSE(tom->hasBullets());
}

TEST_CASE("reload() effect")
{
    Point a(1,2), b(3,4);
    Cowboy *tom = new Cowboy("Tom", a); // Initalized cowboy has 6 bullets
    Cowboy *jerry = new Cowboy("Jerry", b); 

    tom->reload(); // tom get another 6 bullets
    CHECK(tom->getBulletsAmount() == 12);
    
    for (int i = 0; i < 6; ++i) jerry->shoot(tom); // No more bullets for jerry
    jerry->reload(); // 6 bullets for jerry now
    for (int i = 0; i < 5; ++i) jerry->shoot(tom); // Tom is dead

    CHECK_THROWS(tom->reload()); // Dead man can't reload his bullets
}

/* Ninja class */

TEST_CASE("move() correctness")
{
    Point a(1,2), b(30,40), c(15,16), d(22,32);
    YoungNinja *jayson = new YoungNinja("Jayson", a);
    OldNinja *lebron = new OldNinja("Lebron", b);
    Cowboy *nicola = new Cowboy("Nicola", c); 
    Cowboy *jimmy = new Cowboy("Jimmy", d); 

    jayson->move(lebron); // Jason now should be at location (15,16) - his speed is 14
    lebron->move(jayson); // Lebron now should be at location (22,32) - his speed is 8

    CHECK_EQ(jayson->getLocation().getX(), c.getX());
    CHECK_EQ(jayson->getLocation().getY(), c.getY());
    CHECK_EQ(lebron->getLocation().getX(), d.getX());
    CHECK_EQ(lebron->getLocation().getY(), d.getY());

    jayson->move(lebron); // Jason now should be at same location of lebron
    CHECK_EQ(jayson->getLocation().getX(), lebron->getLocation().getX());
    CHECK_EQ(jayson->getLocation().getY(), lebron->getLocation().getY());

    // Jimmy kills nicola
    for (int i = 0; i < 6; ++i) jimmy->shoot(nicola);
    jimmy->reload();
    for (int i = 0; i < 5; ++i) jimmy->shoot(nicola);

    jayson->move(nicola); // Jason didn't move because nicola is dead
    CHECK_EQ(jayson->getLocation().getX(), d.getX());
    CHECK_EQ(jayson->getLocation().getY(), d.getY());
}

TEST_CASE("slash() correctness")
{
    Point a(1,2), b(25,35), c(25.5, 35.5), d(22,32);
    YoungNinja *jayson = new YoungNinja("Jayson", a);
    TrainedNinja *jimmy = new TrainedNinja("Jimmy", b);
    OldNinja *lebron = new OldNinja("Lebron", c);
    
    jayson->slash(jimmy); // Jayson located far than meter from jimmy - no effect 
    CHECK(jimmy->getHitPoints() == 120);

    
    for (int i = 0; i < 2; ++i) jayson->move(jimmy); // now jayson closer than meter to jimmy
    for (int i = 0; i < 3; ++i) jayson->slash(jimmy); 
    CHECK(jimmy->getHitPoints() == 0); // Jimmy should be dead
    
    CHECK_THROWS(jimmy->slash(lebron)); // Dead ninja can't slash
}

/* Team class */

TEST_CASE("Same warrior in different teams")
{
    Point a(1,2);
    YoungNinja *jayson = new YoungNinja("Jayson", a);

    Team celtics(jayson);

    CHECK_THROWS_AS(Team miami(jayson), std::invalid_argument); // Same warrior can't be in different teams
}

TEST_CASE("Adding edge cases")
{
    Point a(1,2), b(25,35), c(25.5, 35.5), d(22,32);
    YoungNinja *jayson = new YoungNinja("Jayson", a);
    YoungNinja *jaylen = new YoungNinja("Jaylen", a);
    YoungNinja *marcus = new YoungNinja("Marcus", b);
    YoungNinja *al = new YoungNinja("Al", b);
    YoungNinja *robert = new YoungNinja("Robert", c);
    YoungNinja *malcolm = new YoungNinja("Malcolm", c);
    YoungNinja *derrick = new YoungNinja("Derrick", d);
    YoungNinja *grant = new YoungNinja("Grant", d);
    YoungNinja *sam = new YoungNinja("Sam", a);
    YoungNinja *payton = new YoungNinja("Payton", a);
    OldNinja *lebron = new OldNinja("Lebron", a);

    Team celtics(jayson);

    CHECK_THROWS(celtics.add(jayson)); // Jayson already in the team

    celtics.add(jaylen);
    celtics.add(marcus);
    celtics.add(al);
    celtics.add(robert);
    celtics.add(malcolm);
    celtics.add(derrick);
    celtics.add(grant);
    celtics.add(sam);
    celtics.add(payton);

    CHECK_THROWS(celtics.add(lebron)); // Team can't has more than 10 warriors.
}

TEST_CASE("atack() correctness and edge cases")
{
    Point a(1,2), b(25,35), c(25.5, 35.5), d(22,32), e(1.5,2.5), f(0,0), g(0,0), h(0,0);

    YoungNinja *jayson = new YoungNinja("Jayson", a);
    YoungNinja *jaylen = new YoungNinja("Jaylen", b);
    YoungNinja *marcus = new YoungNinja("Marcus", c);
    YoungNinja *al = new YoungNinja("Al", d);
    
    Team celtics(jayson);

    YoungNinja *lebron = new YoungNinja("Lebron", e);
    YoungNinja *anthony = new YoungNinja("Anthony", f);
    YoungNinja *austin = new YoungNinja("Dennis", g);
    YoungNinja *dennis = new YoungNinja("Al", h);
  
    Team lakers(lebron);

    celtics.attack(&lakers);

    CHECK_LE(lebron->getHitPoints(), 100); // expecting celtics attack lebron - the most close warrior to jayson

    while (celtics.stillAlive() > 0 && lakers.stillAlive() > 0) celtics.attack(&lakers);

    CHECK_THROWS(lakers.attack(&celtics)); // lakers are all dead, can't attack anymore
}













