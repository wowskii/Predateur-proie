#include "grille.hpp"
#include "doctest.h"


Grille::Grille() {
    cases = vector<vector<int>>(LONGUEUR);
    for (int i = 0; i < LONGUEUR; i++) {
        cases[i] = vector<int>(LARGEUR, -1);
    }
}

TEST_CASE("Constructeur de grille") {
    Grille g{};
    for (int i = 0; i < LONGUEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
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

    //TEST videCase
    g.videCase(Coord(5,5));
    CHECK(g.getCase(Coord(5,5)) == -1);

    //TEST caseVide
    CHECK(g.caseVide(Coord(5,5)));
    CHECK(g.caseVide(Coord(4,7)));
}