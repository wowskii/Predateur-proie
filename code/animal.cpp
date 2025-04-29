#include "animal.hpp"
#include "doctest.h"

int Animal::getId() const {
    return id;
}
TEST_CASE("Animal getId()"){
    Animal a;
    CHECK(a.getId() == 0);
}

Coord Animal::getCoord() const{
    return coord;
}
TEST_CASE("Animal getCoord()"){
    Animal a;
    CHECK(a.getCoord() == Coord(0, 0));
}

Animal::Animal() {
    id = 0;
    coord = Coord(0, 0);
    espece = Lapin;
}

TEST_CASE("Constructeur par defaut"){
    Animal a;
    CHECK(a.getId() == 0);
    CHECK(a.getCoord() == Coord(0, 0));
    CHECK(a.getEspece() == Lapin);
}

void Animal::setCoord(int x, int y){
    coord = Coord(x, y);
}
TEST_CASE("Animal setCoord()"){
    Animal a;
    Coord defaut = a.getCoord();
    CHECK(defaut == Coord(0, 0));

    a.setCoord(3, 5);
    Coord newCoord = a.getCoord();
    CHECK(newCoord == Coord(3, 5));

    a.setCoord(10, 10);
    CHECK(newCoord == Coord(10, 10));
}

void Animal::setEspece(Espece e){
    espece = e;
}

Espece Animal::getEspece() const {
    return espece;
}

void Animal::affiche() {
    cout << "L'identifiant de l'animal est : " << getId() << endl;
    Coord position = getCoord();
    cout << "Coordonnees: (" << position << endl;
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

bool Animal::seReproduire(int voisinVides) const{
    return voisinVides >= 2;
}

void Animal::mange(){
    energie++;
}

void Animal::jeune(){
    energie--;
    if(energie <= 0) meurt();
}

int Animal::getEnergie() const {
    return energie;
}


