#include "Application.h"

Application& Application::getInstance()
{
    static Application instance;

    return instance;
}

void Application::showConfigurationWindow() const
{
    _configurationWindow->setVisibility(true);
}

void Application::hideConfigurationWindow() const
{
    _configurationWindow->setVisibility(false);
}

void Application::init()
{
    auto screenWidht = 0;
    auto screenHeight = 0;

    WindowsApi::getDesktopResolution(screenWidht, screenHeight);

    _wallpaperWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(screenWidht, screenHeight), "Awesome wallpaper", sf::Style::Fullscreen | sf::Style::None);
    _wallpaperWindow->setPosition({0, 0});
    _wallpaperWindow->setFramerateLimit(144);

    _configurationWindow = std::make_unique<ConfigurationWindow>();

    _trayIcon = std::make_unique<TrayIcon>();
}

void Application::run()
{
    while (_isExited == false)
    {
        for (auto event = sf::Event{}; _wallpaperWindow->pollEvent(event);)
        {
        }

        _configurationWindow->dispatchEvents();

        _wallpaperWindow->clear();
        _configurationWindow->clear();

        _wallpaperWindow->display();
        _configurationWindow->display();
    }
}

void Application::exit()
{
    _isExited = true;
}
