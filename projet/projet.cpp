#include "projet.hpp"
#include "doctest.h"

Animal::Animal() {
    id = 0;
    coord = Coord(0, 0);
    espece = Lapin;
}

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

void Animal::affiche() {
    cout << "L'identifiant de l'animal est : " << getId() << endl;
    pair<int, int> position = getCoord();
    cout << "Coordonnees: (" << position.first << ", " << position.second << ")" << endl;
    cout << "Espece : ";
    if (getEspece() == Lapin){
        cout << "Lapin";
    }; 
    if(getEspece() == Renard){
        cout << "Renard";
    }
    else {
        cout << "Espèce inconnu";
    }
}

bool Animal::meurt(){
    estVivant = false;
    return true;
}
