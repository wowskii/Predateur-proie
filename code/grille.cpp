#include "grille.hpp"
#include "doctest.h"


Grille::Grille() {
    cases = vector<vector<int>>(TAILLEGRILLE);
    for (int i = 0; i < TAILLEGRILLE; i++) {
        cases[i] = vector<int>(TAILLEGRILLE, -1);
    }
}

TEST_CASE("Constructeur de grille") {
    Grille g{};
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            CHECK(g.getCase(Coord(i,j)) == -1);
        }
    }
}

bool Grille::caseVide(Coord c) const {
    return cases[c.getLig()][c.getCol()] == -1;
}

int Grille::getCase(Coord c) const {
    return cases[c.getLig()][c.getCol()];
}

void Grille::videCase(Coord c) {
    cases[c.getLig()][c.getCol()] = -1;
}

int Grille::setCase(Coord c, int id) {
    cases[c.getLig()][c.getCol()] = id;
    return id;
}

TEST_CASE("Test general grille") {
    Grille g;
    Population p;

    //TEST setCase
    int test1 = g.setCase(Coord(2,5), p.set(Animal(-1, Lapin, Coord(2,5))));
    int test2 = g.setCase(Coord(5,5), p.set(Animal(-1, Lapin, Coord(5,5))));
    //TEST getCase
    CHECK(g.getCase(Coord(2,5)) == test1);
    CHECK(g.getCase(Coord(5,5)) == test2);
    //cout << g;

    //TEST videCase
    g.videCase(Coord(5,5));
    CHECK(g.getCase(Coord(5,5)) == -1);

    //TEST caseVide
    CHECK(g.caseVide(Coord(5,5)));
    CHECK(g.caseVide(Coord(4,7)));
}

ostream& operator<<(ostream &out, const Grille &g) {
    for (int i = 0; i < TAILLEGRILLE; i++) {
        for (int j = 0; j < TAILLEGRILLE; j++) {
            out << setw(3) << g.getCase(Coord(i,j));
            if (j < TAILLEGRILLE - 1) out << ", ";
        }
        out << endl;
    }
    return out;
}