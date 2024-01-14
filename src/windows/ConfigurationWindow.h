#pragma once
#include <memory>

#include "controls/Button.h"
#include "SFML/Graphics/RenderWindow.hpp"

class ConfigurationWindow {
public:
    ConfigurationWindow();

    void setVisibility(bool visibility) const;

    void display() const;
    void dispatchEvents() const;
    void clear() const;

private:

    bool selectWallpaperButtonClicked();
    bool aboutButtonClicked();
    bool exitButtonClicked();
    
private:
    std::unique_ptr<sf::RenderWindow> _window;
    std::unique_ptr<Button> _selectWallpaperButton;
    std::unique_ptr<Button> _aboutButton;
    std::unique_ptr<Button> _exitButton;
};
