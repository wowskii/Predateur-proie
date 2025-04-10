#include "doctest.h"
#include "coord.hpp"
#include <iostream>

using namespace std;

int TAILLEGRILLE = 40;



Coord::Coord(int coordx, int coordy) : x{coordx}, y{coordy}
{
    if (x < 0 or y < 0 or x > 40 or x > 40) throw invalid_argument("Coordonnées invalides");
}

int Coord::getX(){
    return x;
}

int Coord::getY(){
    return y;
}

TEST_CASE("Constructeur") {
    Coord c1{4,5};
    CHECK(c1.getX() == 4);
    CHECK(c1.getY() == 5);

    CHECK_THROWS_AS(Coord(50, 30), invalid_argument);
}