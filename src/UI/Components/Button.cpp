//
// Created by ahmad on 7/24/2025.
//

#include "./Button.h"

Button::Button(sf::RenderWindow& window, const sf::Font& font, std::wstring&& value, const sf::Vector2f& position,
               const sf::Vector2f& size, const sf::Vector2f& margin, unsigned int fontSize,
               const sf::Color& backgroundColor)
    : Component(window, font, position, size), _pressed(false) {
    _backgroundColor = new sf::Color(backgroundColor);

    _button = new sf::RectangleShape(size);
    _button->setFillColor(backgroundColor);
    _button->setPosition(position + margin);
    _button->setOutlineThickness(1);
    _button->setOutlineColor(sf::Color::Black);

    // TODO: Move margin calculations to the text component
    _text = new Text(window, font, std::move(value), position + margin + sf::Vector2f{size.x / 8.f, size.y / 4.f}, size,
                     fontSize);

    _onPressedCallback = [] {};
}
Button::~Button() {
    Component::~Component();
    delete _button;
    delete _text;
    delete _backgroundColor;
}

void Button::onPressed(const std::function<void()>& onPressedCallback) {
    _onPressedCallback = onPressedCallback;
}

void Button::onEvent(const sf::Event* event) {
    Component::onEvent(event);
    _text->onEvent(event);

    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left &&
            _button->getGlobalBounds().contains(static_cast<sf::Vector2<float>>(mousePressed->position))) {
            _onPressedCallback();
            _pressed = true;
        }
    }

    if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
        if (mouseReleased->button == sf::Mouse::Button::Left && _pressed) {
            _pressed = false;
        }
    }
}

void Button::onFrame() {
    Component::onFrame();

    if (_pressed) {
        _button->setFillColor(sf::Color(15, 34, 52, 100));
    } else if (_button->getFillColor() != *_backgroundColor) {
        _button->setFillColor(*_backgroundColor);
    }
}

void Button::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    target.draw(*_button, states);
    target.draw(*_text, states);
}