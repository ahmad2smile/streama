﻿//
// Created by ahmad on 6/20/2025.
//

#include "Output.h"

#include "src/UI/Graphics/View.h"

Output::Output(sf::RenderWindow& window, const sf::Font& font, std::wstring&& value, const sf::Vector2f& position,
               const sf::Vector2f& size, const sf::Vector2f& margin, const unsigned int fontSize)
    : Text(window, font, std::move(value), position + margin, size - margin * 2.f, fontSize), _scrollSpeed(100) {

    _border = new sf::RectangleShape(size - margin * 2.f);
    _border->setFillColor(sf::Color(15, 34, 52, 255));
    _border->setOutlineColor(sf::Color(54, 56, 57));
    _border->setOutlineThickness(2.f);
    _border->setPosition(position + margin);
    _border->setScale({1, 1});
    _border->setOrigin({0, 0});

    _margin = new sf::Vector2f(margin);

    _scrollView = new View(window, position + margin, size - margin * 2.f);
}

Output::~Output() {
    delete _border;
    delete _margin;
    delete _scrollView;
}

void Output::setSize(const sf::Vector2f& value) {
    const auto adjustValue = value - *_margin * 2.f;

    Text::setSize(adjustValue);
    _border->setSize(adjustValue);
    _scrollView->setSize(adjustValue);
}

sf::Vector2f Output::getSize() const {
    return Text::getSize() + *_margin * 2.f;
}

void Output::setPosition(const sf::Vector2f& value) {
    const auto adjustedValue = value + *_margin;
    Text::setPosition(adjustedValue);
    _border->setPosition(adjustedValue);
    _scrollView->setPosition(adjustedValue + Text::getSize() / 2.f);
}

sf::Vector2f Output::getPosition() const {
    return Text::getPosition() - *_margin;
}

void Output::onEvent(const sf::Event* event) {
    Text::onEvent(event);

    if (const auto e = event->getIf<sf::Event::MouseWheelScrolled>()) {
        const auto delta = e->delta * _scrollSpeed;
        auto outputPosition = _sfText->getPosition();

        _sfText->setPosition({outputPosition.x, outputPosition.y + delta});
    }
}

void Output::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    target.draw(*_border);
    const auto view = target.getView();

    target.setView(*_scrollView);
    Text::draw(target, states);
    target.setView(view);
}
