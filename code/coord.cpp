#include "coord.hpp"
#include "doctest.h"


// Classe Coord
Coord::Coord() {
    lig = 0;
    col = 0;
}

Coord::Coord(int l, int c) : lig{l}, col{c}
{
    if (l < 0 or c < 0 or l >= TAILLEGRILLE or c >= TAILLEGRILLE)
        throw invalid_argument("Valeurs de coordonnées invalides");
}

Coord::Coord(int n)
{
    if (n < 0 or n > TAILLEGRILLE * TAILLEGRILLE - 1)
        throw invalid_argument("Valeur entière invalide");
    int c = n % TAILLEGRILLE;
    int l = n / TAILLEGRILLE;
    lig = l;
    col = c;
}

int Coord::getLig() const
{
    return lig;
}

int Coord::getCol() const
{
    return col;
}

TEST_CASE("Constructeur")
{
    // Cas limite en 0
    Coord c1{0, 0};
    CHECK(c1.getLig() == 0);
    CHECK(c1.getCol() == 0);

    // Cas général
    int rlig = rand() % TAILLEGRILLE;
    int rcol = rand() % TAILLEGRILLE;
    Coord c2{rlig, rcol};
    CHECK(c2.getLig() == rlig);
    CHECK(c2.getCol() == rcol);

    // Cas limite en TAILLEGRILLE-1
    Coord c3{TAILLEGRILLE - 1, TAILLEGRILLE - 1};
    CHECK(c3.getLig() == TAILLEGRILLE - 1);
    CHECK(c3.getCol() == TAILLEGRILLE - 1);

    // Coordonnées invalides
    CHECK_THROWS_AS(Coord(TAILLEGRILLE + 10, 30), invalid_argument);
    CHECK_THROWS_AS(Coord(23, -2), invalid_argument);
}

ostream &operator<<(ostream &out, const Coord &c)
{
    out << "(" << c.getLig() << "," << c.getCol() << ")";
    return out;
}

TEST_CASE("Affichage de coordonnees")
{
    Coord c1{4, 5};
    ostringstream oss1;
    oss1 << c1;
    CHECK(oss1.str() == "(4,5)");
    Coord c2{TAILLEGRILLE - 1, TAILLEGRILLE - 1};
    ostringstream oss2;
    oss2 << c2;
    CHECK(oss2.str() == "(" + to_string(TAILLEGRILLE - 1) + "," + to_string(TAILLEGRILLE - 1) + ")");
}

bool operator==(const Coord &c1, const Coord &c2)
{
    return (c1.getLig() == c2.getLig() && c1.getCol() == c2.getCol());
}

bool operator!=(const Coord &c1, const Coord &c2)
{
    return !(c1 == c2);
}

TEST_CASE("Comparaison de coordonnees")
{
    Coord c1{4, 5};
    Coord c2{4, 5};
    Coord c3{5, 6};

    CHECK(c1 == c2);
    CHECK(c1 != c3);
    CHECK(c2 != c3);
}

int Coord::toInt() const
{
    return lig * TAILLEGRILLE + col;
}

TEST_CASE("Encodage en entiers")
{
    // Cas général
    Coord c1{4, 5};
    CHECK(c1 == Coord{165});

    // Cas limites
    CHECK(Coord{0} == Coord{0, 0});
    CHECK(Coord{1} == Coord{0, 1});
    CHECK(Coord{TAILLEGRILLE} == Coord{1, 0});
    CHECK(Coord{TAILLEGRILLE * TAILLEGRILLE - 1} == Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 1});

    // Cas: entier invalide
    CHECK_THROWS_AS(Coord(TAILLEGRILLE * TAILLEGRILLE), invalid_argument);
    CHECK_THROWS_AS(Coord(-17), invalid_argument);
}

TEST_CASE("Fonction toInt")
{
    for (int i = 0; i < 10; i++)
    {
        int rlig = rand() % TAILLEGRILLE;
        int rcol = rand() % TAILLEGRILLE;

        Coord crand{rlig, rcol};
        CHECK(Coord{crand.toInt()} == crand);
    }
}

Ensemble Coord::voisine() const
{
    Ensemble ev;
    int imin = max(lig - 1, 0);
    int imax = min(lig + 1, TAILLEGRILLE - 1);
    int jmin = max(col - 1, 0);
    int jmax = min(col + 1, TAILLEGRILLE - 1);
    for (int i = imin; i <= imax; i++)
    {
        for (int j = jmin; j <= jmax; j++)
        {
            if ((i != lig) || (j != col))
            {
                ev.ajoute(Coord{i, j}.toInt());
            }
        }
    }
    return ev;
}

TEST_CASE("voisines")
{
    srand(time(0));
    Ensemble ev1;
    ev1 = Coord{0, 0}.voisine();
    ostringstream oss1;
    oss1 << ev1;
    CHECK(oss1.str() == "{(0,1), (1,0), (1,1)}");
    //cout << ev1;

    // Coins de la grille
    Coord coin1 = Coord{0, 0};
    Ensemble evcoin1 = coin1.voisine();
    CHECK(evcoin1.cardinal() == 3);
    Coord coin2 = Coord{TAILLEGRILLE - 1, 0};
    Ensemble evcoin2 = coin2.voisine();
    CHECK(evcoin2.cardinal() == 3);
    Coord coin3 = Coord{0, TAILLEGRILLE - 1};
    Ensemble evcoin3 = coin3.voisine();
    CHECK(evcoin3.cardinal() == 3);
    Coord coin4 = Coord{TAILLEGRILLE - 1, TAILLEGRILLE - 1};
    Ensemble evcoin4 = coin4.voisine();
    CHECK(evcoin4.cardinal() == 3);
    // cout << evcoin1 << evcoin2 << evcoin3 << evcoin4;
    // Bords de la grille
    for (int i = 0; i < 10; i++)
    {
        int l, c;
        int bord = rand() % 4;
        switch (bord)
        {
        case 0:
            l = 1 + (rand() % (TAILLEGRILLE - 2));
            c = 0;
            break;
        case 1:
            l = 0;
            c = 1 + (rand() % (TAILLEGRILLE - 2));
            break;
        case 2:
            l = 1 + (rand() % (TAILLEGRILLE - 2));
            c = TAILLEGRILLE - 1;
            break;
        case 3:
            l = TAILLEGRILLE - 1;
            c = 1 + (rand() % (TAILLEGRILLE - 2));
            break;
        }
        // cout << bord << " " << l << " " << c << endl;
        CHECK(Coord{l, c}.voisine().cardinal() == 5);
    }
}

// Classe Ensemble

void Ensemble::affiche(ostream &out) const
{
    out << "{";
    for (int i = 0; i < card; i++)
    {
        out << Coord(t[i]);
        if (i < card - 1)
            out << ", ";
    }
    out << "}";
}

ostream &operator<<(ostream &out, const Ensemble &e)
{
    e.affiche(out);
    return out;
}
TEST_CASE("Affichage d'ensemble")
{
    Ensemble c1;
    c1.ajoute(2);
    ostringstream oss1;
    oss1 << c1;
    CHECK(oss1.str() == "{(0,2)}");

    c1.tire();
    ostringstream oss2;
    oss2 << c1;
    CHECK(oss2.str() == "{}");

    c1.ajoute(4);
    c1.ajoute(15);
    c1.ajoute(20);
    ostringstream oss3;
    oss3 << c1;
    CHECK(oss3.str() == "{(0,4), (0,15), (0,20)}");
}

Ensemble::Ensemble() : t(MAXCARD, 0), card(0) {};

bool Ensemble::estVide()
{
    return card == 0;
}
TEST_CASE("Fonction estVide")
{
    Ensemble c1;
    CHECK(c1.estVide() == true);

    c1.ajoute(10);
    CHECK(c1.estVide() == false);

    c1.tire();
    CHECK(c1.estVide() == true);
}

int Ensemble::cardinal()
{
    return card;
}
TEST_CASE("Fonction cardinal")
{
    Ensemble c1;
    CHECK(c1.cardinal() == 0);

    c1.ajoute(10);
    CHECK(c1.cardinal() == 1);

    c1.tire();
    CHECK(c1.cardinal() == 0);
}

void Ensemble::ajoute(int a)
{
    if (card >= MAXCARD)
    {
        throw runtime_error("Ajout impossible");
    }
    t[card] = a;
    card++;
}
TEST_CASE("Fonction ajoute")
{
    Ensemble c2;

    CHECK(c2.estVide() == true);
    CHECK(c2.cardinal() == 0);

    c2.ajoute(1);
    CHECK(c2.estVide() == false);
    CHECK(c2.cardinal() == 1);

    c2.ajoute(2);
    CHECK(c2.cardinal() == 2);
}

int Ensemble::tire()
{
    srand(time(0));
    if (estVide())
        throw runtime_error("Retrait impossible");
    int index = rand() % card;
    int randnum = t[index];

    t[index] = t[card - 1];
    card--;

    return randnum;
}
