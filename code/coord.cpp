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
    cout << c1 << endl;
}


ostream& operator<<(ostream& out, const Coord c) {
    cout << "(" << c.getX() << "," << c.getY() << ")";
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
    if(card == 0) return true;
    return false;
}

int Ensemble::cardinal(){
    return card;
}

int Ensemble::ajoute(int a){
    if(card >= MAXCARD){
        throw runtime_error("Ajout impossible");
    }
    t[card] = a;
    card++;
}

