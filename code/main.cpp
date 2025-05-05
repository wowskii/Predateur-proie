#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "graphique.hpp"

using namespace std;
using namespace sf;

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Jeu j(0.2, 0.01);

    RenderWindow w(VideoMode(850, 850), "Simulation");
    w.clear(Color(Color::Green));

    ofstream data("stats/data.csv");
    int nbetape = 0;

    if (!data) {
        cerr << "Erreur lors de l'ouverture du fichier!" << endl;
    }

    while (w.isOpen())
    {

            //while (!(j.cycleFini()))
            //{
                SFMLdessine(j.getGrille(), j.getPopulation(), w);
                j.recenseData(j.etape(), nbetape, data);
                // system("clear");
                // cout << j.getGrille() << endl;
                this_thread::sleep_for(chrono::milliseconds(500));
            //}
            //w.close();
        nbetape++;
    }

    data.close();
    return 0;
}