#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "kernel/WindowsApi.h"
#include "windows/Application.h"
#include "windows/controls/TrayIcon.h"

int main()
{
    auto& application = Application::getInstance();

    application.init();
    application.run();
    
    /*const auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920u, 1080u), "CMake SFML Project");
    window->setFramerateLimit(144);

    TrayIcon trayIcon;

    //auto data = WindowsApi::setupTrayIcon(window.getSystemHandle(), "icon.ico");

    while (window->isOpen())
    {
        for (auto event = sf::Event{}; window->pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
                std::cout << "mose pressed!!!";
        }

        window->clear();
        window->display();
    }*/

    //WindowsApi::deleteTrayIcon(data);
}
