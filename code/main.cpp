#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "jeu.hpp"


int main () {
    srand(static_cast<unsigned int>(time(0)));

    Jeu j(0.4,0.1);

    while(!(j.cycleFini())){
        j.afficher();
        j.etape();
        system("clear");
    }

}