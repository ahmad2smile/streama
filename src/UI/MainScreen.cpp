//
// Created by ahmad on 7/24/2025.
//

#include "MainScreen.h"

MainScreen::MainScreen(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position,
                       const sf::Vector2f& size)
    : Component(window, font, position, size) {
    const auto windowSize = window.getSize();
    const auto windowWidth = static_cast<float>(windowSize.x);

    const auto outputSize = sf::Vector2f(windowWidth, 60);

    _loginButton = new Button(window, font, L"Login", {0, 0}, {100, 60}, {10, 10});
    _output = new Output(window, font, L"", {0, 80}, {windowWidth, outputSize.y}, {10, 10}, 25);
}
MainScreen::~MainScreen() {
    delete _output;
    delete _loginButton;
}
void MainScreen::onEvent(const sf::Event* event) {
    Component::onEvent(event);
    _output->onEvent(event);
    _loginButton->onEvent(event);

    if (const auto e = event->getIf<sf::Event::Resized>()) {
        const auto inputHeight = _output->getSize().y;
        const auto newWidth = static_cast<float>(e->size.x);

        _output->setSize({newWidth, _output->getSize().y});
    }
}
void MainScreen::onFrame() {
    Component::onFrame();
    _loginButton->onFrame();
}

void MainScreen::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    target.draw(*_loginButton, states);
    target.draw(*_output, states);
}