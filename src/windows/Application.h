#pragma once

#include <memory>

#include "ConfigurationWindow.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include "controls/TrayIcon.h"

class Application
{
private:
    Application(): _isExited(false) { }

public:
    Application(const Application& other) = delete;
    Application& operator=(const Application& other) = delete;
    Application(Application&& other) = delete;
    Application& operator=(Application&& other) = delete;

    static Application& getInstance();

    void showConfigurationWindow() const;
    void hideConfigurationWindow() const;

    void init();
    void run();
    void exit();

private:
    bool _isExited;

    std::unique_ptr<sf::RenderWindow> _wallpaperWindow;
    std::unique_ptr<ConfigurationWindow> _configurationWindow;
    std::unique_ptr<TrayIcon> _trayIcon;
};
