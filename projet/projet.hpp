#ifndef COORD_HPP
#define COORD_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

class Ensemble { 
    private :
        vector<int> t;
        int card;
        static const int MAXCARD = 100;

    public :
        Ensemble();
        bool estVide();
        int cardinal();
        void affiche(ostream &out) const;
        friend ostream& operator<<(ostream& out, const Ensemble& e);
        void ajoute(int a);
        int tire();
};

class Coord
{
private:
    int lig;
    int col;

public:
    Coord();
    Coord(int lig, int col);
    Coord(int n);

    int getLig() const;
    int getCol() const;
    Ensemble voisine() const;
    int toInt() const;
};


enum Espece {
    Lapin,
    Renard
};

class Animal{
    private :
        int id;
        Coord coord;
        Espece espece;
    public:
        Animal();
        int getId() const;
        pair<int, int> getCoord() const;
        void setCoord(int x, int y);
        void setEspece(Espece e);
        Espece getEspece() const;
        void affiche();
        
};

#endif