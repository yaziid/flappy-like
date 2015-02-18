#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>

int main()
{
    int const pige = 6; // le nombre de piège
    int const pospiege = 4000;
    float const gravite = 1;
    int const terre = 300;
    int const speed = 6; // normalement 6
    sf::Vector2f velocite;
    sf::View vue;
    bool vie = true; // bool pour savoir si tjr en vie val par défaut true
    bool gen = true; // bool pour génération des pièges val par défaut true
    bool feu = false; // savoir si flamme ou projectile val par défaut true
    sf::Texture flammes;
    sf::Sprite flame[pige];
    sf::Texture arriere;
    sf::Sprite ground[pige];
    sf::Sprite bac[pige];
    sf::Texture milieu;
    sf::Sprite millieu[pige];
    sf::Texture balon;
    sf::Sprite ballon;
    sf::Sprite flame_h[pige];
    sf::Font font;
    sf::Text score;
    std::string scores;
    std::stringstream ss;
    sf::RectangleShape proj[pige];
    sf::ContextSettings settings;
    int bouclepiege = 0;

    settings.antialiasingLevel = 8;

    sf::RenderWindow app(sf::VideoMode(800, 600), "Jeu Yaz", sf::Style::Default, settings);

    app.setFramerateLimit(60);

    vue.setSize(800, 600);

    srand(time(NULL));

    if(!flammes.loadFromFile("Yazid.png"))
    {
        std::cout<<"Erreur chargement texture"<<std::endl;
    }

    if(!arriere.loadFromFile("back.png"))
    {
        std::cout<<"Erreur chargement texture"<<std::endl;
    }

    if(!milieu.loadFromFile("milieu.png"))
    {
        std::cout<<"Erreur chargement texture"<<std::endl;
    }

    if(!balon.loadFromFile("ballon.png"))
    {
        std::cout<<"Erreur chargement texture"<<std::endl;
    }

    if(!font.loadFromFile("arial.ttf"))
    {
        std::cout<<"Erreur chargement police"<<std::endl;
    }

    flammes.setSmooth(true);
    arriere.setSmooth(true);
    milieu.setSmooth(true);
    balon.setSmooth(true);

    for(int k = 0; k < pige; k++) // sprite piege
    {
        flame[k].setTexture(flammes);
    }

    for(int k = 0; k < pige; k++) // sprite piege haut
    {
        flame_h[k].setTexture(flammes);
        flame_h[k].rotate(180);
    }

    for(int l = 0; l < pige; l++) // sprite back haut
    {
        ground[l].setTexture(arriere);
        ground[l].setPosition((l * 800), 0 - 350);
    }

    for(int l = 0; l < pige; l++) // sprite back bas
    {
        bac[l].setTexture(arriere);
        bac[l].setPosition((l * 800), 300);
    }

    for(int l = 0; l < pige; l++) // sprite back milieu
    {
        millieu[l].setTexture(milieu);
        millieu[l].setPosition((l * 800), 0);
    }

    ballon.setTexture(balon);
    ballon.setPosition(-60, 250);

    // gestion du score
    score.setFont(font);
    score.setString("Score: 0");
    score.setCharacterSize(24);
    score.setColor(sf::Color::White);
    score.setStyle(sf::Text::Bold);

    while (app.isOpen())
    {
        //gestion du score
        ss.str("");
        ss<<ballon.getPosition().x;
        scores = ss.str();
        vue.setCenter(ballon.getPosition());
        score.setString("Score: "+ scores);
        score.setPosition(ballon.getPosition().x - 350, -40);

        sf::Event event;

        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                app.close();
            }
                if(event.type == sf::Event::KeyPressed) // juste pour le debug a enlever dans la final release !
                {
                    if(event.key.code == sf::Keyboard::T)
                    {
                        vie = true;
                        ballon.setPosition(ballon.getPosition().x, 160);
                    }
                }
        }

        if(vie) // si le joueur est tjr en vie
        {
            for(int i = 0; i < 2; i++)
            {
                if(ground[i].getPosition().x + 800 < ballon.getPosition().x )
                {
                    ground[i].setPosition(ballon.getPosition().x, -350); // millieu
                    bac[i].setPosition(ballon.getPosition().x, 300);
                    millieu[i].setPosition(ballon.getPosition().x, 0);

                    ground[i + 1].setPosition(ballon.getPosition().x - 800, -350); // derrière
                    bac[i + 1].setPosition(ballon.getPosition().x - 800, 300);
                    millieu[i + 1].setPosition(ballon.getPosition().x - 800, 0);

                    ground[i + 2].setPosition(ballon.getPosition().x + 800, -350); // devant
                    bac[i + 2].setPosition(ballon.getPosition().x + 800, 300);
                    millieu[i + 2].setPosition(ballon.getPosition().x + 800, 0);
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                velocite.x = -speed;
            }

            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                velocite.x = speed;
            }

            else
            {
                velocite.x = 0;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                velocite.y = -8;
            }


            if(ballon.getPosition().y + 30 < terre || velocite.y < 0)
            {
                velocite.y += gravite;
            }
            else
            {
                ballon.setPosition(ballon.getPosition().x, terre - 30);
                velocite.y = 0;
            }

            if(ballon.getPosition().y < 0)
            {
                ballon.setPosition(ballon.getPosition().x, 0);
            }

            ballon.move(velocite.x, velocite.y);
            vue.move(velocite);

            if(feu)
            {
                if(ballon.getPosition().x - 850 > flame[pige - 1].getPosition().x && ballon.getPosition().x - 850 > flame_h[pige - 1].getPosition().x)
                {
                    gen = true;
                }

                if(ballon.getPosition().x > pospiege && gen) // gestion des pièges
                {
                    for(int i = 0; i < pige; i++)
                    {
                        int tmp = rand() % (int(ballon.getPosition().x) + 1050) + (int(ballon.getPosition().x) + 850); // piege bas
                        int tmmp = rand() % (int(ballon.getPosition().x) + 1050) + (int(ballon.getPosition().x) + 850); // piege haut

                        flame[i].setPosition(tmp, terre - 79);
                        flame_h[i].setPosition(tmmp, 0 + 79);

                        if(flame[i - 1].getGlobalBounds().intersects(flame[i].getGlobalBounds())) // pour eviter que les flames soit proche
                        {
                            tmp = rand() % (int(ballon.getPosition().x) + 1050) + (int(ballon.getPosition().x) + 850);
                            flame[i].setPosition(tmp, terre - 79);
                        }

                        if(flame_h[i - 1].getGlobalBounds().intersects(flame_h[i].getGlobalBounds()))
                        {
                            tmmp = rand() % (int(ballon.getPosition().x) + 1050) + (int(ballon.getPosition().x) + 850);
                            flame_h[i].setPosition(tmmp, 0 + 79);
                        }

                        gen = false;

                        if(bouclepiege >= 2 && ballon.getPosition().x > flame[pige - 1].getPosition().x && ballon.getPosition().x > flame_h[pige - 1].getPosition().x)
                        {
                            feu = false;
                            bouclepiege = 0;
                        }

                    }

                    bouclepiege++;
                }
            }

            if(feu == false)
            {
                int tmmp = rand() % 4 + 0;

                for(int i = 0; i < tmmp; i++)
                {
                    int tmp = rand() % 300 + 0;

                    proj[i].setSize(sf::Vector2f(10, 10));
                    proj[i].setOutlineColor(sf::Color::Red);
                    proj[i].setOutlineThickness(5);
                    proj[i].setPosition(ballon.getPosition().x + 850, tmp);

                    feu = true;
                }

            }

            for(int i = 0; i < pige; i++)
            {
                proj[i].move(-3, 0);
            }

            for(int i = 0; i < 3; i++) // s'il touche en haut ou en bas
            {
                if(ballon.getGlobalBounds().intersects(ground[i].getGlobalBounds()) || ballon.getGlobalBounds().intersects(bac[i].getGlobalBounds())) // gamer over
                {
                    vie = false;
                    score.setColor(sf::Color::Red);
                }
            }


            for(int i = 0; i < pige; i++)
            {
                if(ballon.getGlobalBounds().intersects(flame[i].getGlobalBounds()) ||
                   ballon.getGlobalBounds().intersects(flame_h[i].getGlobalBounds())) // s'il touche un piège
                {
                    if(ballon.getPosition().x > pospiege)
                    {
                        vie = false;
                        score.setColor(sf::Color::Red);
                    }
                }
            }
        }

        app.clear();

        app.setView(vue);
        for(int i = 0; i < pige; i++) // affichage back haut et bas
        {
            app.draw(ground[i]); // haut
            app.draw(bac[i]); // bas
            app.draw(millieu[i]); // millieu
            app.draw(proj[i]); // projectiles
        }
        for(int j = 0; j < pige; j++) // affichage piege flamme
        {
            if(ballon.getPosition().x > pospiege)
            {
                app.draw(flame[j]);
                app.draw(flame_h[j]);
            }
        }
        app.draw(score);
        app.draw(ballon);

        app.display();
    }

    return EXIT_SUCCESS;
}
