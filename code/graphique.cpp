#include "graphique.hpp"

using namespace std;
using namespace sf;

void SFMLdessine(Grille g, Population p, RenderWindow &w)
{
    Texture lapinTexture, renardTexture, fondTexture;
    if (!lapinTexture.loadFromFile("resources/lapin.png"))
    {
        cerr << "Error loading lapin.png" << endl;
        return;
    }
    if (!renardTexture.loadFromFile("resources/renard.png"))
    {
        cerr << "Error loading renard.png" << endl;
        return;
    }
    if (!fondTexture.loadFromFile("resources/fond1.png"))
    {
        cerr << "Error loading fond.png" << endl;
        return;
    }

    w.clear();

    Sprite fond;
    fond.setTexture(fondTexture);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int pos_x = (380 * j);
            int pos_y = (380 * i);

            fond.setScale(0.5,0.5);
            fond.setPosition(pos_x, pos_y);
            w.draw(fond);
        }
    }

    for (int i = 0; i < TAILLEGRILLE; i++)
    {
        for (int j = 0; j < TAILLEGRILLE; j++)
        {
            int pos_x = (10 + 17 * j);
            int pos_y = (10 + 17 * i);

            // int pos_x_text = pos_x + 20;
            // int pos_y_text = pos_y + 10;


            if (g.getCase(Coord(i, j)) != -1)
            {
                Sprite sprite;
                switch (p.get(g.getCase(Coord(i, j))).getEspece())
                {
                case (Espece::Lapin):
                    sprite.setTexture(lapinTexture);
                    break;
                case (Espece::Renard):
                    sprite.setTexture(renardTexture);
                    break;
                }
                sprite.setPosition(pos_x, pos_y);
                w.draw(sprite);
            }
            // else
            // {
            //     RectangleShape tuile(Vector2f(19.f, 19.f));
            //     tuile.setPosition(pos_x, pos_y);
            //     tuile.setFillColor(Color::Green);
            //     w.draw(tuile);
            // }
        }
    }
    w.display();
}
