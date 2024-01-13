#pragma once

#include <functional>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class Button {

public:
    Button(const std::string& text, const sf::Vector2f& size);

    Button() = delete;

    void draw(sf::RenderWindow& window) const;
    void handleEvent(const sf::Event& event) const;

    void setCharacterSize(unsigned int size);
    void setTextPosition(const sf::Vector2f& position);
    void setPosition(const sf::Vector2f& position);
    void setFillColor(const sf::Color& color);
    void setFont(const sf::Font& font);

    void subscribeOnClick(const std::function<bool()>& func);
private:
    sf::Text _text;
    sf::RectangleShape _rectangle;

    std::vector<std::function<bool()>> _onClickSubscribers;
};
