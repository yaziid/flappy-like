#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int const pige = 4; // le nombre de piège
    sf::RenderWindow app(sf::VideoMode(800, 600), "Jeu Yaz");
    float const gravite = 1;
    int terre = 300;
    int speed = 50; // normalement 5
    sf::Vector2f velocite;
    sf::View vue;
    bool vie = true; // bool pour savoir si tjr en vie
    sf::RectangleShape piege[pige];
    bool gen = true; // bool pour génération des pièges
    sf::Texture flammes;
    sf::Sprite flame[pige];
    sf::Texture arriere;
    sf::Sprite ground[pige];
    sf::Sprite bac[pige];
    sf::Texture milieu;
    sf::Sprite millieu[pige];
    sf::Texture balon;
    sf::Sprite ballon;

    plate.setSize(sf::Vector2f(20000, 1));
    plate.setFillColor(sf::Color::Yellow);
    plate.setPosition(0, terre);

    haut.setSize(sf::Vector2f(20000, 1));
    haut.setFillColor(sf::Color::Yellow);
    haut.setPosition(0, 0);

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

    flammes.setSmooth(true);
    arriere.setSmooth(true);
    milieu.setSmooth(true);
    balon.setSmooth(true);

    for(int k = 0; k < pige; k++) // sprite piege
    {
        flame[k].setTexture(flammes);
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
    ballon.setPosition(-20, 10);

    while (app.isOpen())
    {
        vue.setCenter(ballon.getPosition());

        sf::Event event;

        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                app.close();
            }

        }

        if(vie) // si le joueur est tjr en vie
        {
            for(int i = 0; i < 2; i++)
            {
                if(ground[i].getPosition().x + 800  < ballon.getPosition().x )
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

                    std::cout<<"ballon"<<ballon.getPosition().x<<std::endl;
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

            if(ballon.getPosition().x > 8000 && gen) // gestion des pièges
            {
                for(int i = 0; i < pige; i++)
                {
                    int tmp = rand() % 10000 + 8000;

                    piege[i].setSize(sf::Vector2f(7, -70));
                    piege[i].setFillColor(sf::Color::Yellow);
                    piege[i].setPosition(tmp, terre);

                    std::cout<<"piege !! i = "<<i<<" lautre truc: "<<piege[i].getPosition().x<<std::endl;

                    flame[i].setPosition(tmp - 20, terre - 79);

                    gen = false;
                }
            }

            for(int i = 0; i < 3; i++) // s'il touche en haut ou en bas
            {
                if(ballon.getGlobalBounds().intersects(ground[i].getGlobalBounds()) || ballon.getGlobalBounds().intersects(bac[i].getGlobalBounds())) // gamer over
                {
                    vie = false;
                    std::cout<<"votre score est "<<ballon.getPosition().x<<std::endl;
                }
            }

            if(ballon.getGlobalBounds().intersects(piege[0].getGlobalBounds()) ||
               ballon.getGlobalBounds().intersects(piege[1].getGlobalBounds()) ||
               ballon.getGlobalBounds().intersects(piege[2].getGlobalBounds()) ||
               ballon.getGlobalBounds().intersects(piege[3].getGlobalBounds()) ||
               ballon.getGlobalBounds().intersects(piege[4].getGlobalBounds()) // s'il touche un piège
               )
            {
                vie = false;
                std::cout<<"votre score est "<<ballon.getPosition().x<<std::endl;
            }
        }

        app.clear();

        app.setView(vue);
        for(int i = 0; i < pige; i++) // affichage back haut et bas
        {
            app.draw(ground[i]); // haut
            app.draw(bac[i]); // bas
            app.draw(millieu[i]); // millieu
        }
        app.draw(ballon);
        for(int j = 0; j < pige; j++) // affichage piege flamme
        {
            if(ballon.getPosition().x > 8000)
            {
                app.draw(piege[j]);
                app.draw(flame[j]);
            }
        }

        app.display();
    }

    return EXIT_SUCCESS;
}
