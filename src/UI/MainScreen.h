//
// Created by ahmad on 7/24/2025.
//

#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include "Components/Button.h"
#include "Components/Component.h"
#include "Components/Output.h"


class MainScreen final : public Component {
public:
    [[nodiscard]] MainScreen(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position,
                             const sf::Vector2f& size);

    ~MainScreen() override;

    void onEvent(const sf::Event* event) override;

    void onFrame() override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Button* _loginButton;
    Output* _output;
};


#endif //MAINSCREEN_H
