#include <iostream>
#include <glm.hpp>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#include "Game.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Survivor Arena",sf::Style::Fullscreen);
    sf::Event event;
    Game* game = new Game(window);
    game->init(&window);
    static sf::Clock clock; // Create a static clock to measure time
    
    
    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                game->close();
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            game->get_players()[0]->moveLeft(deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            game->get_players()[0]->moveUp(deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            game->get_players()[0]->moveDown(&window,deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            game->get_players()[0]->moveRight(&window,deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            game->get_players()[1]->moveLeft(deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            game->get_players()[1]->moveUp(deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            game->get_players()[1]->moveDown(&window,deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            game->get_players()[1]->moveRight(&window,deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            game->get_players()[0]->shoot(window);
        }
        
        game->update(deltaTime,&window);
        game->display(&window);
        window.display();
    }
   
}

