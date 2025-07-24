//
// Created by ahmad on 7/24/2025.
//

#ifndef BUTTON_H
#define BUTTON_H
#include "Component.h"
#include "Text.h"

#include <functional>
#include <SFML/Graphics/RectangleShape.hpp>


class Button final : public Component {
public:
    Button(sf::RenderWindow& window, const sf::Font& font, std::wstring&& value = L"",
           const sf::Vector2f& position = {0, 0}, const sf::Vector2f& size = {18, 18},
           const sf::Vector2f& margin = {10, 10}, unsigned int fontSize = 24,
           const sf::Color& backgroundColor = sf::Color(15, 34, 52, 255));

    ~Button() override;

    void onPressed(const std::function<void()>& onPressedCallback);

    void onEvent(const sf::Event* event) override;

    void onFrame() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    bool _pressed;
    const sf::Color* _backgroundColor;
    std::function<void()> _onPressedCallback;
    sf::RectangleShape* _button;
    Text* _text;
};


#endif //BUTTON_H
