#include "jeu.hpp"
#include "doctest.h"

Jeu::Jeu(float probLapins, float probRenard)
{
    if (probLapins < 0 || probLapins > 1 ||
        probRenard < 0 || probRenard > 1 ||
        probLapins + probRenard > 1)
        throw invalid_argument("Les probabilités, ainsi que leur somme, doit être comprises entre 0 et 1");
    float probVide = 1 - probLapins - probRenard;

    int probLapinsPourCent = 100 * probLapins;
    int probRenardPourCent = 100 * probRenard;
    srand(time(0));
    for (int i = 0; i < TAILLEGRILLE * TAILLEGRILLE; i++)
    {
        int r = rand() % 100;
        Coord c(i);

        if (r < probLapinsPourCent)
            ajouteAnimal(Lapin, c);
        else if (r < probLapinsPourCent + probRenardPourCent)
            ajouteAnimal(Renard, c);
    }
    // cout << g;
}

TEST_CASE("Test visuel Constructeur Jeu")
{
    Jeu j(0.4, 0.1);
}

int Jeu::ajouteAnimal(Espece e, Coord c)
{
    int id = g.setCase(c, p.set(Animal(-1, e, c)));
    return id;
}

void Jeu::afficher() const
{
    for (int k = 0; k < TAILLEGRILLE*3+1; k++){
        cout << '-';
    }
    cout << endl;
    Ensemble ids = p.getIds();
    int card = ids.cardinal();
    for (int i = 0; i < TAILLEGRILLE; i++)
    {
        cout << "|";
        for (int j = 0; j < TAILLEGRILLE; j++)
        {
            if (!g.caseVide(Coord(i,j))) {
                Espece e = p.get(g.getCase(Coord(i,j))).getEspece();
                if (e == Espece::Lapin) cout << "L";
                else cout << "R";
            }
            else cout << " ";
            cout << setw(2) << "|";
        }
        cout << endl;
        for (int k = 0; k < TAILLEGRILLE*3+1; k++){
            cout << '-';
        }
        cout << endl;
    }
}

TEST_CASE("Test visuel affichage") {
    Jeu j(0.4, 0.1);
    j.afficher();
}