#include "animal.hpp"
#include "doctest.h"

int Animal::getId() const {
    return id;
}
TEST_CASE("Animal getId()"){
    Animal a;
    CHECK(a.getId() == -1);
}

void Animal::setId(int newid) {
    id = newid;
}

Coord Animal::getCoord() const{
    return coord;
}
TEST_CASE("Animal getCoord()"){
    Animal a;
    CHECK(a.getCoord() == Coord(0, 0));
}

Animal::Animal() : id(-1), espece(Lapin), coord(0, 0), estVivant(false), energie(0) {};

TEST_CASE("Constructeur par defaut"){
    Animal a;
    CHECK(a.getId() == -1);
    CHECK(a.getCoord() == Coord(0, 0));
    CHECK(a.getEspece() == Lapin);
}

void Animal::setCoord(Coord c){
    coord = c;
}
TEST_CASE("Animal setCoord()"){
    Animal a;
    Coord defaultCoord = a.getCoord();
    CHECK(defaultCoord == Coord(0, 0));

    SUBCASE("Test avec Coord valide") {
        Coord testCoord(3, 5);
        a.setCoord(testCoord);
        CHECK(a.getCoord() == testCoord);
        CHECK(a.getCoord().getLig() == 3);
        CHECK(a.getCoord().getCol() == 5);
    }
    SUBCASE("Test avec Coord invalide") {
        CHECK_THROWS_AS(Coord(-1, -1), std::invalid_argument);
        CHECK_THROWS_AS(Coord(TAILLEGRILLE, TAILLEGRILLE), std::invalid_argument);
    }
}

void Animal::setEspece(Espece e){
    espece = e;
}
TEST_CASE("Animal setEspece()"){
    Animal a;
    a.setEspece(Renard);
    CHECK(a.getEspece() == Renard);
}

Espece Animal::getEspece() const {
    return espece;
}
TEST_CASE("Animal getEspece()"){
    Animal a;
    CHECK(a.getEspece() == Lapin);

    a.setEspece(Renard);
    CHECK(a.getEspece() == Renard);
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
    return energie <= 0;
}
TEST_CASE("Animal meurt()"){
    Animal a;
    CHECK(a.meurt() == true);
    a.mange(); 
    CHECK(a.meurt() == false);
}

bool Animal::seReproduire(int voisinVides) const{
    return voisinVides >= 2;
}
TEST_CASE("Animal seReproduire()"){
    Animal a;
    CHECK(a.seReproduire(0) == false);
    CHECK(a.seReproduire(1) == false);
    CHECK(a.seReproduire(2) == true);
    CHECK(a.seReproduire(3) == true);
}

int Animal::getEnergie() const {
    return energie;
}

void Animal::mange(){
    energie++;
}
TEST_CASE("Animal mange()"){
    Animal a;
    int test = a.getEnergie();
    a.mange();
    CHECK(a.getEnergie() == test + 1);
}

void Animal::jeune(){
    energie--;
}
TEST_CASE("Aninmal mange()"){
    Animal a;
    a.mange();
    a.jeune();
    CHECK(a.getEnergie() == 0);
    a.mange();
    a.mange();
    a.jeune();
    CHECK(a.getEnergie() == 1);
}

bool Animal::isVivant() const{
    return estVivant;
}




