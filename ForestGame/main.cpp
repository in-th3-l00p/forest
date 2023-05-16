#include <SFML/Graphics.hpp>
#include "Map.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    Engine::Map map;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) 
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                break;
            }
        }

        window.clear();
        map.renderMinimap(window, 100);
        window.display();
    }

    return 0;
}