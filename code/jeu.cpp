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
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dx++){
            if(dx == 0 && dy == 0) continue;
            
            Coord voisin(x + dx, y + dy);
            if((voisin.getLig() >= 0 && voisin.getLig() <= TAILLEGRILLE) && (voisin.getCol() >= 0 && voisin.getCol() <= TAILLEGRILLE)){
                if(!g.caseVide(voisin)){
                    int id = g.getCase(voisin);
                    const Animal& animal = p.get(id);
                    if(animal.getEspece() == e){
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
    
    Jeu j(0.0, 0.0f);
    
    Coord centre = Coord{2, 2}; 
    
    j.ajouteAnimal(Espece::Renard, centre);
    j.ajouteAnimal(Espece::Lapin, Coord{1, 2}); 
    j.ajouteAnimal(Espece::Lapin, Coord{3, 2}); 
    j.ajouteAnimal(Espece::Renard, Coord{2, 1}); 
    
   
    Ensemble voisinsLapins = j.voisinsEspece(centre, Espece::Lapin);
    
   
    CHECK(voisinsLapins.cardinal() == 2); 
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