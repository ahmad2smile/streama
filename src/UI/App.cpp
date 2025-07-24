//
// Created by ahmad on 10.12.23.
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "App.h"

#include "MainScreen.h"
#include "Components/Command.h"

namespace UI {
    App::App() = default;

    sf::RenderWindow* App::initialize(const unsigned int width, const unsigned int height, const char* title) {
        const auto video_mode = sf::VideoMode::getDesktopMode();
        const auto size = sf::Vector2u{video_mode.size.x / 2, video_mode.size.y / 2};

        const auto window = new sf::RenderWindow(sf::VideoMode({size}), title);

        window->setView(sf::View(sf::FloatRect({0, 0}, {static_cast<float>(size.x), static_cast<float>(size.y)})));

        // NOTE: To avoid screen tearing
        window->setVerticalSyncEnabled(true);
        window->setFramerateLimit(60);

        if (!_font.openFromFile("FiraCodeNerdFont-Light.ttf")) {
            // error...
            std::cout << "Error loading font" << std::endl;
        }

        return window;
    }

    void App::run(sf::RenderWindow& window) const {
        DbContext dbContext;
        dbContext.initTables();

        const auto engine = new ExecutionEngine(dbContext);
        const auto windowSize = window.getSize();
        const auto windowHeight = static_cast<float>(windowSize.y);
        const auto windowWidth = static_cast<float>(windowSize.x);

        MainScreen mainScreen(window, _font, {0, 0}, {windowWidth, windowHeight});

        while (window.isOpen()) {
            while (const auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                if (const auto e = event->getIf<sf::Event::Resized>()) {
                    window.setView(sf::View(
                            sf::FloatRect({0, 0}, {static_cast<float>(e->size.x), static_cast<float>(e->size.y)})));
                }

                mainScreen.onEvent(&event.value());
            }

            mainScreen.onFrame();

            window.clear(sf::Color(2, 5, 23));
            window.draw(mainScreen);
            window.display();
        }
    }
} // namespace UI
