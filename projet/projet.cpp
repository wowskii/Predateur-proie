#include "projet.hpp"
#include "doctest.h"

int Animal::getId() const {
    return id;
}

pair<int, int> Animal::getCoord() const{
    return make_pair(coord.getLig(), coord.getCol());
}

void Animal::setCoord(int x, int y){
    coord = Coord(x, y);
}

void Animal::setEspece(Espece e){
    espece = e;
}

Espece Animal::getEspece() const {
    return espece;
}

