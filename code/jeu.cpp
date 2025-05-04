#include "jeu.hpp"
#include "doctest.h"

const int Jeu::MinFreeBirthLapin = 4;
const float Jeu::ProbReproLapin = 0.3f;

const int Jeu::FoodInit = 5;
const int Jeu::FoodLapin = 5;
const int Jeu::FoodReprod = 8;
const int Jeu::MaxFood = 10;
const float Jeu::ProbBirthRenard = 0.05f;

Animal Jeu::getAnimal(int id) {
    return p.get(id);  // Maintenant valide car p.get() retourne une référence valide
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
    int id = g.setCase(c, p.set(Animal(-1, e, c, true, FoodInit)));
    return id;
}

int Jeu::mortAnimal(Animal a) {
    p.supprime(a.getId());
    g.videCase(a.getCoord());
    return a.getId();
}
TEST_CASE("Jeu::mortAnimal()") {
    Jeu j(0.0, 0.0);
    Coord c(5, 5);
    Coord voisin(5,6);

    int id = j.ajouteAnimal(Espece::Lapin, c);
    CHECK(j.getAnimal(id).getCoord() == c);

    Animal a = j.getAnimal(id);
    j.mortAnimal(a);

    CHECK(j.voisinsVides(voisin).cardinal() == 8);
}

void Jeu::verifieGrille() const {
    for (int id : p.getIds()) {
        const Animal& animal = p.get(id);
        Coord coord = animal.getCoord();
        
        if (g.getCase(coord) != id) {
            throw std::runtime_error("Erreur: Animal " + std::to_string(id) + " mal placé ");
        }
    }
}
TEST_CASE("Jeu::verifieGrille()"){
    Jeu jeu(0.0, 0.0);
    Coord c(2,3);
    int test = jeu.ajouteAnimal(Lapin, c);
    CHECK_NOTHROW(jeu.verifieGrille());
}

Ensemble Jeu::voisinsVides(Coord c) const{
    Ensemble res;
    int x = c.getLig();
    int y = c.getCol();
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            if(dx == 0 && dy == 0) continue;

            Coord voisin(x + dx, y + dy);
            if(g.caseVide(voisin)) {
                int coord = voisin.getLig() * TAILLEGRILLE + voisin.getCol();
                res.ajoute(coord);
            }
        }
    }
    return res;
}
TEST_CASE("Jeu::voisinsVides()"){
    Jeu j(0.0, 0.0); 
    Coord c(1, 1);
    j.ajouteAnimal(Lapin, c); 
    Ensemble vides = j.voisinsVides(c);
    CHECK(vides.cardinal() == 8);
}

Ensemble Jeu::voisinsEspece(Coord c, Espece e) const{
    Ensemble res;
    int x = c.getLig();
    int y = c.getCol();
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;

            Coord voisin(x + dx, y + dy);
            
            if (voisin.getLig() >= 0 && voisin.getLig() < TAILLEGRILLE && voisin.getCol() >= 0 && voisin.getCol() < TAILLEGRILLE) {
                if (!g.caseVide(voisin)) {
                    int id = g.getCase(voisin);
                    const Animal& animal = p.get(id);
                    if (animal.getEspece() == e) {
                        int coord = voisin.getLig() * TAILLEGRILLE + voisin.getCol();
                        res.ajoute(coord);
                    }
                }
            }
        }
    }
    return res;
}
TEST_CASE("Jeu::voisinsEspece()"){
    Jeu j(0.0, 0.0); 
   
    Coord centre(10, 10); 
   
    j.ajouteAnimal(Espece::Renard, centre);
    j.ajouteAnimal(Espece::Lapin, Coord(9, 10));  
    j.ajouteAnimal(Espece::Lapin, Coord(11, 10));
    j.ajouteAnimal(Espece::Renard, Coord(10, 9)); 

    Ensemble voisinsLapins = j.voisinsEspece(centre, Espece::Lapin);
    Ensemble voisinsRenards = j.voisinsEspece(centre, Espece::Renard);

    CHECK(voisinsLapins.cardinal() == 2);
    CHECK(voisinsRenards.cardinal() == 1);
}

void Jeu::deplacerAnimal(Animal &a){
    Coord anciennepos = a.getCoord();
    Ensemble caseslibres = voisinsVides(anciennepos);

    if(!caseslibres.estVide()){
        Coord nouvellepos = caseslibres.tire();
        g.videCase(anciennepos);
        g.setCase(nouvellepos, a.getId());
        a.setCoord(nouvellepos);
    }
}
TEST_CASE("Jeu::deplacerAnimal()"){
    Jeu j(0.0f, 0.0f);
    int id = j.ajouteAnimal(Espece::Lapin, Coord(2, 2));
    Animal a = j.getAnimal(id);
        
    CHECK(a.getCoord() == Coord(2, 2));
    CHECK(j.voisinsVides(Coord(2, 2)).cardinal() == 8);
        
    j.deplacerAnimal(a);
        
    Coord newPos = a.getCoord();
    
    CHECK_FALSE(newPos == Coord(2, 2));
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

void Jeu::testCoherence() const {
    Ensemble ids = p.getIds();
    for (auto id : ids) {
        if (p.get(id).getId() != id)
            throw runtime_error ("Incohérence d'identifiant dans la population. Identifiant stocké par la population : "
            + to_string(id) + ". Identifiant stocké par l'animal : " + to_string(p.get(id).getId()));
    }
    verifieGrille();
}


// Méthodes touchant au fonctionnement du jeu

void Jeu::etape() {
    Ensemble ids = p.getIds();
    //Comportement Lapins
    for (auto id: ids) {
        Animal a = p.get(id);
        int voisinsvides_initial = voisinsVides(a.getCoord()).cardinal();
        Coord c_initial;
        if (a.getEspece() == Espece::Lapin) {
            deplacerAnimal(a);
            //Reproduction de lapins
            if (voisinsvides_initial >= MinFreeBirthLapin) {
                if (rand() % 100 < ProbReproLapin * 100) {
                    ajouteAnimal(Lapin, c_initial);
                }
            }
        }
    }
    //Comportement Renards
    for (auto id: ids) {
        Animal a = p.get(id);
        int voisinsvides_initial = voisinsVides(a.getCoord()).cardinal();
        Coord c_initial;
        //Mort de faim
        a.setEnergie(a.getEnergie() - 1);
        if (a.getEnergie() <= 0) {
            mortAnimal(a);
        }
        Ensemble voisinslapins_initial = voisinsEspece(c_initial, Lapin);
        //Chasse aux lapins
        if (voisinslapins_initial.cardinal() > 0) {
            if(!voisinslapins_initial.estVide()){
                Coord nouvellepos = voisinslapins_initial.tire();
                g.videCase(c_initial);
                mortAnimal(p.get(g.getCase(nouvellepos)));
                g.setCase(nouvellepos, a.getId());
                a.setCoord(nouvellepos);
                a.setEnergie(a.getEnergie() + FoodLapin);
            }
        }
        else deplacerAnimal(a);
        //Reproduction
        if (a.getEnergie() >= FoodReprod) {
            if (rand() % 100 < ProbBirthRenard * 100) {
                ajouteAnimal(Renard, c_initial);
            }
        }
    }
}