#include "coord.hpp"
#include "doctest.h"


int TAILLEGRILLE = 40;

Coord::Coord(int coordx, int coordy) : x{coordx}, y{coordy}
{
    if (x < 0 or y < 0 or x > 40 or x > 40) throw invalid_argument("Coordonnées invalides");
}

int Coord::getX() const{
    return x;
}

int Coord::getY() const{
    return y;
}

TEST_CASE("Constructeur") {
    Coord c1{4,5};
    CHECK(c1.getX() == 4);
    CHECK(c1.getY() == 5);
    CHECK_THROWS_AS(Coord(50, 30), invalid_argument);
}


ostream& operator<<(ostream& out, const Coord& c) {
    out << "(" << c.getX() << "," << c.getY() << ")";
    return out;
}

int Coord::toInt() const {
    return x * (TAILLEGRILLE + 1) + y;
}


void Ensemble::affiche(ostream &out) const{
    out << "{ ";
    for (int i = 0; i < card; i++) {
        out << t[i];
        if (i < card - 1) out << ", ";
    }
    out << " }";
}

ostream& operator<<(ostream& out, const Ensemble& e) {
    e.affiche(out);
    return out;
}

Ensemble::Ensemble() : t(MAXCARD, 0), card(0) {};

bool Ensemble::estVide(){
    return card == 0;
}
TEST_CASE("Fonction estVide"){
    Ensemble c1;
    CHECK(c1.estVide() == true);

    c1.ajoute(10);
    CHECK(c1.estVide() == false);

    c1.tire();
    CHECK(c1.estVide() == true);
}

int Ensemble::cardinal(){
    return card;
}
TEST_CASE("Fonction cardinal"){
    Ensemble c1;
    CHECK(c1.cardinal() == 0);

    c1.ajoute(10);
    CHECK(c1.cardinal() == 1);

    c1.tire();
    CHECK(c1.cardinal() == 0);
}

void Ensemble::ajoute(int a){
    if(card >= MAXCARD){
        throw runtime_error("Ajout impossible");
    }
    t[card] = a;
    card++;
}
TEST_CASE("Fonction ajoute"){
    Ensemble c2;

    CHECK(c2.estVide() == true);
    CHECK(c2.cardinal() == 0);

    c2.ajoute(1);
    CHECK(c2.estVide() == false);
    CHECK(c2.cardinal() == 1);

    c2.ajoute(2);
    CHECK(c2.cardinal() == 2);
}

int Ensemble::tire(){
    if(estVide()) throw runtime_error("Retrait impossible");
    int index = rand() % card;
    int randnum = t[index];

    t[index] = t[card - 1];
    card--;

    return randnum;
}

