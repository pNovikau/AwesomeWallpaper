#include "ConfigurationWindow.h"

#include "Application.h"
#include "kernel/WindowsApi.h"
#include "SFML/Window/Event.hpp"

ConfigurationWindow::ConfigurationWindow()
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Configuration", sf::Style::Close | sf::Style::Titlebar);
    _window->setVisible(false);

    sf::Font font;
    if (!font.loadFromFile("Roboto-Bold.ttf"))
    {
        throw std::runtime_error("Error loading font.");
    }

    _selectWallpaperButton = std::make_unique<Button>("Select Wallpaper", sf::Vector2f(200, 50));
    _selectWallpaperButton->setFont(font);
    _selectWallpaperButton->setCharacterSize(20);
    _selectWallpaperButton->setTextPosition({50, 50});
    _selectWallpaperButton->setFillColor(sf::Color::Green);
    _selectWallpaperButton->setPosition({45, 45});

    _selectWallpaperButton->subscribeOnClick([this]() { return this->selectWallpaperButtonClicked(); });

    _aboutButton = std::make_unique<Button>("About", sf::Vector2f(200, 50));
    _aboutButton->setFont(font);
    _aboutButton->setCharacterSize(20);
    _aboutButton->setTextPosition({50, 50});
    _aboutButton->setFillColor(sf::Color::Blue);
    _aboutButton->setPosition({145, 45});

    _aboutButton->subscribeOnClick([this]() { return this->aboutButtonClicked(); });

    _exitButton = std::make_unique<Button>("Exit", sf::Vector2f(200, 50));
    _exitButton->setFont(font);
    _exitButton->setCharacterSize(20);
    _exitButton->setTextPosition({50, 50});
    _exitButton->setFillColor(sf::Color::Red);
    _exitButton->setPosition({245, 45});

    _exitButton->subscribeOnClick([this]() { return this->exitButtonClicked(); });
}

void ConfigurationWindow::setVisibility(const bool visibility) const
{
    _window->setVisible(visibility);
}

void ConfigurationWindow::display() const
{
    _selectWallpaperButton->draw(*_window);
    _aboutButton->draw(*_window);
    _exitButton->draw(*_window);

    _window->display();
}

void ConfigurationWindow::dispatchEvents() const
{
    for (auto event = sf::Event{}; _window->pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
            setVisibility(false);

        _selectWallpaperButton->handleEvent(event);
        _aboutButton->handleEvent(event);
        _exitButton->handleEvent(event);
    }
}

void ConfigurationWindow::clear() const
{
    _window->clear();
}

bool ConfigurationWindow::selectWallpaperButtonClicked()
{
    WindowsApi::openSelectFileDialog("MP4 Files\0*.mp4\0");

    return true;
}

bool ConfigurationWindow::aboutButtonClicked()
{
    return true;
}

bool ConfigurationWindow::exitButtonClicked()
{
    auto& application = Application::getInstance();
    application.exit();

    return true;
}
