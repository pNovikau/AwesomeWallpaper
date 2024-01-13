#include "Button.h"

#include "SFML/Window/Event.hpp"

Button::Button(const std::string& text, const sf::Vector2f& size)
{
    _text = sf::Text();
    _text.setString(text);

    _rectangle = sf::RectangleShape(size);
}

void Button::draw(sf::RenderWindow& window) const
{
    window.draw(_text);
    window.draw(_rectangle);
}

void Button::handleEvent(const sf::Event& event) const
{
    if (event.type != sf::Event::MouseButtonPressed)
        return;

    const auto mousePositionX = static_cast<float>(event.mouseButton.x);
    const auto mousePositionY = static_cast<float>(event.mouseButton.y);

    if (_rectangle.getGlobalBounds().contains(mousePositionX, mousePositionY) == false)
        return;

    for (const auto& subscriber : _onClickSubscribers)
    {
        if (subscriber() == false)
            return;
    }
}

void Button::setCharacterSize(const unsigned size)
{
    _text.setCharacterSize(size);
}

void Button::setTextPosition(const sf::Vector2f& position)
{
    _text.setPosition(position);
}

void Button::setPosition(const sf::Vector2f& position)
{
    _rectangle.setPosition(position);
}

void Button::setFillColor(const sf::Color& color)
{
    _rectangle.setFillColor(color);
}

void Button::setFont(const sf::Font& font)
{
    _text.setFont(font);
}

void Button::subscribeOnClick(const std::function<bool()>& func)
{
    _onClickSubscribers.push_back(func);
}
