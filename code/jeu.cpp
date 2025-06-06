#include "jeu.hpp"
#include "doctest.h"

int Jeu::MinFreeBirthLapin = 4;
float Jeu::ProbReproLapin = 0.3f;
int Jeu::FoodInit = 5;
int Jeu::FoodLapin = 5;
int Jeu::FoodReprod = 8;
int Jeu::MaxFood = 10;
int Jeu::AgeReprod = 15;
float Jeu::ProbBirthRenard = 0.05f;

Animal Jeu::getAnimal(int id)
{
    return p.get(id);
}
Jeu::Jeu(float probLapins, float probRenard)
{
    if (probLapins < 0 || probLapins > 1 ||
        probRenard < 0 || probRenard > 1 ||
        probLapins + probRenard > 1)
        throw invalid_argument("Les probabilités, ainsi que leur somme, doit être comprises entre 0 et 1");
    float probVide = 1 - probLapins - probRenard;

    int probLapinsPourCent = 100 * probLapins;
    int probRenardPourCent = 100 * probRenard;
    for (int i = 0; i < TAILLEGRILLE * TAILLEGRILLE; i++)
    {
        int r = rand() % 100;
        Coord c(i);

        if (r < probLapinsPourCent)
        {
            Sexe s = (rand() % 2 == 0) ? Sexe::M : Sexe::F;
            ajouteAnimal(Lapin, c, s);
        }
        else if (r < probLapinsPourCent + probRenardPourCent)
        {
            Sexe s = (rand() % 2 == 0) ? Sexe::M : Sexe::F;
            ajouteAnimal(Renard, c, s);
        }
    }
    // cout << g;
}

TEST_CASE("Test visuel Constructeur Jeu")
{
    Jeu j(0.2, 0.01);
}

Grille Jeu::getGrille()
{
    return g;
}

Population Jeu::getPopulation()
{
    return p;
}

int Jeu::ajouteAnimal(Espece e, Coord c, Sexe s)
{
    Animal a(-1, e, c, s, true, FoodInit);
    int id = p.set(a);
    g.setCase(c, id);
    // cout << "adding animal id: " << id << " at " << c << " " << g.getCase(c) << endl;
    //  adding is all normal
    //  cout << g << endl;
    return id;
}

int Jeu::mortAnimal(int id)
{
    // std::cout << "Removing Animal ID: " << id << " aka " << g.getCase(p.get(id).getCoord()) << " from Coord: (" << p.get(id).getCoord() << std::endl;
    Coord c = p.get(id).getCoord();
    g.videCase(c);
    p.supprime(id);
    return id;
}
TEST_CASE("Jeu::mortAnimal()")
{
    Jeu j(0.0, 0.0);
    Coord c(5, 5);
    Coord voisin(5, 6);

    int id = j.ajouteAnimal(Espece::Lapin, c, Sexe::F);
    CHECK(j.getAnimal(id).getCoord() == c);

    j.mortAnimal(id);

    CHECK(j.voisinsVides(voisin).cardinal() == 8);
}

void Jeu::verifieGrille() const
{
    for (int id : p.getIds())
    {
        const Animal &animal = p.get(id);
        Coord coord = animal.getCoord();

        if (g.getCase(coord) != id)
        {
            throw runtime_error("Erreur: Animal " + to_string(id) + " mal placé aux coordonnees (" + to_string(coord.getLig()) + ", " + to_string(coord.getCol()) + "). Animal trouvé dans cette position de la grille : ID : " + to_string(g.getCase(coord)) + ". Position de l'animal " + to_string(id) + " d'après Population: (" + to_string(p.get(id).getCoord().getCol()) + ", " + to_string(p.get(id).getCoord().getCol()) + ").");
        }
    }
}
TEST_CASE("Jeu::verifieGrille()")
{
    Jeu jeu(0.0, 0.0);
    Coord c(2, 3);
    int test = jeu.ajouteAnimal(Lapin, c, Sexe::M);
    CHECK_NOTHROW(jeu.verifieGrille());
}

Ensemble Jeu::voisinsVides(Coord c) const
{
    // Ensemble res;
    // int x = c.getLig();
    // int y = c.getCol();
    // for(int dx = -1; dx <= 1; dx++){
    //     for(int dy = -1; dy <= 1; dy++){
    //         if(dx == 0 && dy == 0) continue;

    //         Coord voisin(x + dx, y + dy);
    //         if(g.caseVide(voisin)) {
    //             int coord = voisin.getLig() * TAILLEGRILLE + voisin.getCol();
    //             res.ajoute(coord);
    //         }
    //     }
    // }
    // return res;
    {
        Ensemble ev;
        int imin = max(c.getLig() - 1, 0);
        int imax = min(c.getLig() + 1, TAILLEGRILLE - 1);
        int jmin = max(c.getCol() - 1, 0);
        int jmax = min(c.getCol() + 1, TAILLEGRILLE - 1);
        for (int i = imin; i <= imax; i++)
        {
            for (int j = jmin; j <= jmax; j++)
            {
                if (((i != c.getLig()) || (j != c.getCol())) && g.caseVide(Coord(i, j)))
                {
                    ev.ajoute(Coord{i, j}.toInt());
                }
            }
        }
        // cout << ev << endl;
        return ev;
    }
}
TEST_CASE("Jeu::voisinsVides()")
{
    Jeu j(0.0, 0.0);
    Coord c(1, 1);
    j.ajouteAnimal(Lapin, c, Sexe::M);
    Ensemble vides = j.voisinsVides(c);
    CHECK(vides.cardinal() == 8);

    Coord c2(TAILLEGRILLE - 1, TAILLEGRILLE - 1);
    j.ajouteAnimal(Lapin, c2, Sexe::F);
    Ensemble vides2 = j.voisinsVides(c2);
    CHECK(vides2.cardinal() == 3);
}

Ensemble Jeu::voisinsEspece(Coord c, Espece e) const
{
    //     Ensemble res;
    //     int x = c.getLig();
    //     int y = c.getCol();
    //     for (int dx = -1; dx <= 1; dx++) {
    //         for (int dy = -1; dy <= 1; dy++) {
    //             if (dx == 0 && dy == 0) continue;

    //             Coord voisin(x + dx, y + dy);

    //             if (voisin.getLig() >= 0 && voisin.getLig() < TAILLEGRILLE && voisin.getCol() >= 0 && voisin.getCol() < TAILLEGRILLE) {
    //                 if (!g.caseVide(voisin)) {
    //                     int id = g.getCase(voisin);
    //                     const Animal& animal = p.get(id);
    //                     if (animal.getEspece() == e) {
    //                         int coord = voisin.getLig() * TAILLEGRILLE + voisin.getCol();
    //                         res.ajoute(coord);
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     return res;
    Ensemble ev;
    int imin = max(c.getLig() - 1, 0);
    int imax = min(c.getLig() + 1, TAILLEGRILLE - 1);
    int jmin = max(c.getCol() - 1, 0);
    int jmax = min(c.getCol() + 1, TAILLEGRILLE - 1);
    for (int i = imin; i <= imax; i++)
    {
        for (int j = jmin; j <= jmax; j++)
        {
            Coord voisin = Coord(i, j);
            if ((i != c.getLig() || j != c.getCol()) && !g.caseVide(voisin))
            {
                int id = g.getCase(voisin);
                const Animal &animal = p.get(id);
                if (animal.getEspece() == e)
                {
                    ev.ajoute(voisin.toInt());
                }
            }
        }
    }
    return ev;
}
TEST_CASE("Jeu::voisinsEspece()")
{
    Jeu j(0.0, 0.0);

    Coord centre(10, 10);

    j.ajouteAnimal(Espece::Renard, centre, Sexe::F);
    j.ajouteAnimal(Espece::Lapin, Coord(9, 10), Sexe::M);
    j.ajouteAnimal(Espece::Lapin, Coord(11, 10), Sexe::M);
    j.ajouteAnimal(Espece::Renard, Coord(10, 9), Sexe::F);

    Ensemble voisinsLapins = j.voisinsEspece(centre, Espece::Lapin);
    Ensemble voisinsRenards = j.voisinsEspece(centre, Espece::Renard);

    CHECK(voisinsLapins.cardinal() == 2);
    CHECK(voisinsRenards.cardinal() == 1);
    j.voisinsEspece(Coord(39, 39), Renard);
}

bool Jeu::peutReproduire(const Coord &c, Espece e, Sexe sexe)
{
    int imin = max(c.getLig() - 1, 0);
    int imax = min(c.getLig() + 1, TAILLEGRILLE - 1);
    int jmin = max(c.getCol() - 1, 0);
    int jmax = min(c.getCol() + 1, TAILLEGRILLE - 1);
    for (int i = imin; i <= imax; i++)
    {
        for (int j = jmin; j <= jmax; j++)
        {
            Coord voisin(i, j);
            if ((i != c.getLig() || j != c.getCol()) && !g.caseVide(voisin))
            {
                int id = g.getCase(voisin);
                const Animal &animal = p.get(id);
                if (animal.getEspece() == e && animal.getSexe() != sexe)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
TEST_CASE("Jeu::peutReproduire()")
{
    Jeu jeu(0.0, 0.0);
    Coord centre(5, 5);

    int id_centre = jeu.ajouteAnimal(Lapin, centre, Sexe::M);

    Animal a_centre = jeu.getAnimal(id_centre);
    a_centre.SetSexe(M);
    jeu.getPopulation().updateAnimal(id_centre, a_centre);

    Sexe sexe_centre = a_centre.getSexe();

    SUBCASE("Un partenaire du sexe opposé est présent")
    {
        int id_partenaire = jeu.ajouteAnimal(Lapin, Coord(5, 6), Sexe::F);

        Animal a_partenaire = jeu.getAnimal(id_partenaire);
        a_partenaire.SetSexe(F); // Corrected method name
        jeu.getPopulation().updateAnimal(id_partenaire, a_partenaire);

        CHECK(jeu.peutReproduire(centre, Lapin, sexe_centre) == true);
    }

    SUBCASE("Même sexe → ne peut pas se reproduire")
    {
        int id_partenaire = jeu.ajouteAnimal(Lapin, Coord(5, 6), Sexe::M);
        Animal a_partenaire = jeu.getAnimal(id_partenaire);
        a_partenaire.SetSexe(M); // Corrected method name
        jeu.getPopulation().updateAnimal(id_partenaire, a_partenaire);

        CHECK(jeu.peutReproduire(centre, Lapin, sexe_centre) == false);
    }
}

void Jeu::reproduire(int id, Coord c_initial)
{
    Animal a = p.get(id);

    if (a.getEspece() == Espece::Lapin)
    {
        if ((rand() % 100 < (ProbReproLapin * 100)) && (voisinsEspece(a.getCoord(), Lapin).cardinal() > 0) && voisinsVides(a.getCoord()).cardinal() >= MinFreeBirthLapin && a.getAge() > AgeReprod && peutReproduire(a.getCoord(), Lapin, a.getSexe()))
        {
            bool VoisinAssezAge = false;
            for (auto CoordVoisin : voisinsEspece(a.getCoord(), Lapin))
            {
                if (p.get(g.getCase(CoordVoisin)).getAge() > AgeReprod)
                    VoisinAssezAge = true;
            }
            if (VoisinAssezAge)
            {
                Sexe s = (rand() % 2 == 0) ? Sexe::M : Sexe::F;
                ajouteAnimal(Lapin, c_initial, s);
            }
        }
    }

    else if (a.getEspece() == Espece::Renard)
    {
        if ((rand() % 100 < (ProbBirthRenard * 100)) && (voisinsEspece(a.getCoord(), Renard).cardinal() > 0) && voisinsVides(a.getCoord()).cardinal() > 3 && a.getEnergie() >= FoodReprod && a.getAge() > AgeReprod && peutReproduire(a.getCoord(), Renard, a.getSexe()))
        {
            bool VoisinAssezAge = false;
            for (auto CoordVoisin : voisinsEspece(a.getCoord(), Renard))
            {
                if (p.get(g.getCase(CoordVoisin)).getAge() > AgeReprod)
                    VoisinAssezAge = true;
            }
            if (VoisinAssezAge)
            {
                Sexe s = (rand() % 2 == 0) ? Sexe::M : Sexe::F;
                ajouteAnimal(Renard, c_initial, s);
                // cout << a.getAge() << endl;
            }
        }
    }
}

void Jeu::deplacerAnimal(Animal &a)
{
    Coord anciennepos = a.getCoord();
    Ensemble caseslibres = voisinsVides(anciennepos);

    if (!caseslibres.estVide())
    {
        Coord nouvellepos = caseslibres.tire();

        g.videCase(anciennepos);
        g.setCase(nouvellepos, a.getId());
        a.setCoord(nouvellepos);
        p.updateAnimal(a.getId(), a);

        // std::cout << "Animal ID: " << a.getId() << " " << a.getCoord() << " moved from (" << anciennepos.getLig() << ", " << anciennepos.getCol()
        //           << ") to (" << nouvellepos.getLig() << ", " << nouvellepos.getCol() << ")" << std::endl;
        // testCoherence();
    }
}
TEST_CASE("Jeu::deplacerAnimal()")
{
    Jeu j(0.0f, 0.0f);
    int id = j.ajouteAnimal(Espece::Lapin, Coord(2, 2), Sexe::F);
    Animal a = j.getAnimal(id);

    CHECK(a.getCoord() == Coord(2, 2));
    CHECK(j.voisinsVides(Coord(2, 2)).cardinal() == 8);

    j.deplacerAnimal(a);

    Coord newPos = a.getCoord();

    CHECK_FALSE(newPos == Coord(2, 2));
}

void Jeu::afficher() const
{
    for (int k = 0; k < TAILLEGRILLE * 3 + 1; k++)
    {
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
            if (!g.caseVide(Coord(i, j)))
            {
                Espece e = p.get(g.getCase(Coord(i, j))).getEspece();
                if (e == Espece::Lapin)
                    cout << "L";
                else
                    cout << "R";
            }
            else
                cout << " ";
            cout << setw(2) << "|";
        }
        cout << endl;
        for (int k = 0; k < TAILLEGRILLE * 3 + 1; k++)
        {
            cout << '-';
        }
        cout << endl;
    }
}

// TEST_CASE("Test visuel affichage")
// {
//     Jeu j(0.4, 0.1);
//     j.afficher();
// }

void Jeu::testCoherence() const
{
    for (auto id : p.getIds())
    {
        if (p.get(id).getId() != id)
            throw runtime_error("Incohérence d'identifiant dans la population. Identifiant stocké par la population : " + to_string(id) + ". Identifiant stocké par l'animal : " + to_string(p.get(id).getId()));
    }
    verifieGrille();
}

// Méthodes touchant au fonctionnement du jeu

pair<int, int> Jeu::etape()
{
    int popLapins = 0;
    int popRenards = 0;
    int compteur = 0;
    Ensemble ids = p.getIds();

    for (int i = 0; i < ids.cardinal(); i++)
    {
        int id = ids.tire();
        Animal a = p.get(id);
        if (a.getId() == -1)
            continue;
        // Comportement Commun
        // Mort de vieillisement
        a.vieillir();
        if (a.esttropVieux())
        {
            mortAnimal(id);
            // cout << "Animal mort de vieillissement id: " << id << endl;
            continue;
        }
        // cout << id << " " << compteur << " " << p.getIds().cardinal() << endl;
        // compteur++;

        // Comportement Lapins
        if (a.getEspece() == Espece::Lapin)
        {
            popLapins++;

            Coord c_initial = a.getCoord();

            deplacerAnimal(a);

            // Reproduction de lapins
            reproduire(id, c_initial);
            p.updateAnimal(id, a);
        }
        // Comportement Renards
        else if (a.getEspece() == Renard)
        {
            popRenards++;
            int voisinsvides_initial = voisinsVides(a.getCoord()).cardinal();
            Coord c_initial = a.getCoord();
            // Mort de faim
            a.setEnergie(max(0, a.getEnergie() - 1));
            if (a.getEnergie() == 0)
            {
                mortAnimal(id);
                continue;
            }
            Ensemble voisinslapins_initial = voisinsEspece(c_initial, Lapin);
            // Chasse aux lapins
            if (voisinslapins_initial.cardinal() > 0)
            {
                if (!voisinslapins_initial.estVide())
                {
                    Coord nouvellepos = voisinslapins_initial.tire();
                    g.videCase(c_initial);
                    mortAnimal(g.getCase(nouvellepos));
                    g.setCase(nouvellepos, id);
                    a.setCoord(nouvellepos);
                    a.setEnergie(max(a.getEnergie() + FoodLapin, MaxFood));
                    p.updateAnimal(id, a);
                }
            }
            else
                deplacerAnimal(a);
            // Reproduction de renards
            reproduire(id, c_initial);
        }
        p.updateAnimal(id, a);
    }
    testCoherence();
    return make_pair(popLapins, popRenards);
}

bool Jeu::cycleFini() const
{
    bool AbsenceRenard = true;
    for (auto id : p.getIds())
    {
        if (p.get(id).getEspece() == Renard)
            AbsenceRenard = false;
    }
    bool AbsenceLapin = true;
    for (auto id : p.getIds())
    {
        if (p.get(id).getEspece() == Lapin)
            AbsenceLapin = false;
    }
    return (AbsenceLapin || AbsenceRenard);
}

void Jeu::recenseData(pair<int, int> pop, int etape, ostream &fichier) const
{
    if (etape == 0)
    {
        fichier << "Moment de la simulation, Population de lapins, Population de renards" << endl;
    }
    else if (etape > 0)
        fichier << etape << "," << pop.first << "," << pop.second << endl;
}

void Jeu::choisirParametres()
{
    char ouinon;
    do
    {
        cout << "Voulez-vous utiliser les paramètres des simulation par défaut? (Y: Oui / N: Customiser les paramètres)" << endl;
        cin >> ouinon;
    } while (!(ouinon == 'Y' || ouinon == 'N' || ouinon == 'y' || ouinon == 'n'));
    if (ouinon == 'Y' || ouinon == 'y')
        return;
    else
    {
        do
        {
            cout << "Entrez la probabilité de reproduction des lapins, entre 0 et 1 (par exemple: 0.2, 1.0, valeur par défaut: 0.3)" << endl;
            cin >> ProbReproLapin;
            if (!(ProbReproLapin >= 0. && ProbReproLapin <= 1.))
                cout << "Valeur invalide. Veuillez entrer une valeur entre 0 et 1." << endl;
        } while (!(ProbReproLapin >= 0. && ProbReproLapin <= 1.));

        do
        {
            cout << "Entrez la probabilité de reproduction des renards, entre 0 et 1 (par exemple: 0.05, valeur par défaut: 0.05)" << endl;
            cin >> ProbBirthRenard;
            if (!(ProbBirthRenard >= 0. && ProbBirthRenard <= 1.))
                cout << "Valeur invalide. Veuillez entrer une valeur entre 0 et 1." << endl;
        } while (!(ProbBirthRenard >= 0. && ProbBirthRenard <= 1.));

        do
        {
            cout << "Entrez la quantité initiale de nourriture pour les animaux (par exemple: 5, valeur par défaut: 5)" << endl;
            cin >> FoodInit;
            if (!(FoodInit >= 0))
                cout << "Valeur invalide. Veuillez entrer une valeur supérieure à 0." << endl;
        } while (!(FoodInit >= 0));

        do
        {
            cout << "Entrez la quantité de nourriture gagnée par un renard lorsqu'il mange un lapin (par exemple: 5, valeur par défaut: 5)" << endl;
            cin >> FoodLapin;
            if (!(FoodLapin >= 0))
                cout << "Valeur invalide. Veuillez entrer une valeur supérieure ou égale à 0." << endl;
        } while (!(FoodLapin >= 0));

        do
        {
            cout << "Entrez la quantité de nourriture nécessaire pour qu'un renard puisse se reproduire (par exemple: 8, valeur par défaut: 8)" << endl;
            cin >> FoodReprod;
            if (!(FoodReprod >= 0))
                cout << "Valeur invalide. Veuillez entrer une valeur supérieure ou égale à 0." << endl;
        } while (!(FoodReprod >= 0));

        do
        {
            cout << "Entrez la quantité maximale de nourriture qu'un animal peut avoir (par exemple: 10, valeur par défaut: 10)" << endl;
            cin >> MaxFood;
            if (!(MaxFood > 0))
                cout << "Valeur invalide. Veuillez entrer une valeur supérieure ou égale à 0." << endl;
        } while (!(MaxFood > 0));

        do
        {
            cout << "Entrez l'âge minimum pour qu'un animal puisse se reproduire (par exemple: 15, valeur par défaut: 15)" << endl;
            cin >> AgeReprod;
            if (!(AgeReprod >= 0))
                cout << "Valeur invalide. Veuillez entrer une valeur supérieure ou égale à 0." << endl;
        } while (!(AgeReprod >= 0));

        do
        {
            cout << "Entrez le nombre minimum de cases vides nécessaires pour qu'un lapin puisse se reproduire (par exemple: 4, valeur par défaut: 4)" << endl;
            cin >> MinFreeBirthLapin;
            if (!(MinFreeBirthLapin > 0))
                cout << "Valeur invalide. Veuillez entrer une valeur supérieure à 0." << endl;
        } while (!(MinFreeBirthLapin > 0));
    }
}