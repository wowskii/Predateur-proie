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

void Grille::setCase(Coord c, int id) {
    cases[c.getLig()][c.getCol()] = id;
}

// TEST_CASE("Test general") {
//     Grille g;
//     Population p;
//     int id = reserve();
//     p.set(id, )
// }