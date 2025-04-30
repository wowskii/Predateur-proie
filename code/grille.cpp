#include "grille.hpp"
#include "doctest.h"

bool Grille::caseVide(int x, int y) const {
    return !cases[x][y].isVivant();
}