#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "graphique.hpp"

using namespace std;
using namespace sf;

pair<float, float> initialisationProb()
{
    float probLapin = 0.2;
    float probRenard = 0.02;
    char ouinon;
    do
    {
        cout << "Voulez-vous utiliser les probabilités de création de simulation par défaut? (Y: Oui / N: Customiser les probabilités)" << endl;
        cin >> ouinon;
    } while (!(ouinon == 'Y' || ouinon == 'N' || ouinon == 'y' || ouinon == 'n'));
    if (ouinon == 'Y' || ouinon == 'y')
        return make_pair(probLapin, probRenard);;
    do
    {
        cout << "Entrez la probabilité de présence initiale des lapins, entre 0 et 1 (par exemple: 0.2, valeur par défaut: 0.2)" << endl;
        cin >> probLapin;
        if (!(probLapin >= 0. && probLapin <= 1.))
        {
            cout << "Valeur invalide! Veuillez entrer un nombre entre 0 et 1." << endl;
        }
    } while (!(probLapin >= 0. && probLapin <= 1.));

    do
    {
        cout << "Entrez la probabilité de présence initiale des renards, entre 0 et 1 (par exemple: 0.02, valeur par défaut: 0.05)" << endl;
        cin >> probRenard;
        if (!(probRenard >= 0. && probRenard <= 1.))
        {
            cout << "Valeur invalide! Veuillez entrer un nombre entre 0 et 1." << endl;
        }
    } while (!(probRenard >= 0. && probRenard <= 1.));
    return make_pair(probLapin, probRenard);
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    pair<float, float> prob = initialisationProb();
    Jeu j(prob.first, prob.second);

    j.choisirParametres();

    RenderWindow w(VideoMode(700, 700), "Simulation");
    w.clear(Color(Color::Green));

    ofstream data("stats/data.csv");
    if (!data)
    {
        cerr << "Erreur lors de l'ouverture du fichier!" << endl;
    }
    int nbetape = 0;

    while (w.isOpen())
    {

        while (!(j.cycleFini()))
        {
            SFMLdessine(j.getGrille(), j.getPopulation(), w);
            j.recenseData(j.etape(), nbetape, data);
            // system("clear");
            // cout << j.getGrille() << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
            nbetape++;
        }
        w.close();

    }

    data.close();
    return 0;
}