#include "projet.hpp"
#include "doctest.h"

int Animal::getId() const {
    return id;
}

pair<int, int> Animal::getCoord() const{
    return make_pair(coord.getLig(), coord.getCol());
}

