#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "graphique.hpp"

using namespace std;
using namespace sf;

int main () {
    srand(static_cast<unsigned int>(time(0)));

    Jeu j(0.4,0.1);

    RenderWindow w(VideoMode(850, 850), "Simulation");

    while (w.isOpen())
    {

    while(!(j.cycleFini())){
        SFMLdessine(j.getGrille(), j.getPopulation(), w);
        j.etape();
        system("clear");
    }

}
}