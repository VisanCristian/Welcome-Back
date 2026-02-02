#include "headers/Lucas.h"
#include "headers/InvalidConfigFile.h"
#include <SFML/Graphics.hpp>

Lucas::Lucas() = default;
Lucas::~Lucas() = default;

Option Lucas::spawn() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Lucas Spawn");

    sf::Font font;
    if (!font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        throw InvalidConfigFile("Could not open font");
    }

    sf::Text option1(font, "hide", 30);
    option1.setFillColor(sf::Color::White);
    option1.setPosition({350.0f, 200.0f});

    sf::Text option2(font, "change network connection", 30);
    option2.setFillColor(sf::Color::White);
    option2.setPosition({250.0f, 300.0f});

    sf::Text option3(font, "turn around and stand still", 30);
    option3.setFillColor(sf::Color::White);
    option3.setPosition({240.0f, 400.0f});

    Option selectedOption = Option::Hide;
    bool optionSelected = false;

    while (window.isOpen() && !optionSelected) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButton->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                    if (option1.getGlobalBounds().contains(mousePosF)) {
                        selectedOption = Option::Hide;
                        optionSelected = true;
                    } else if (option2.getGlobalBounds().contains(mousePosF)) {
                        selectedOption = Option::ChangeConnection;
                        optionSelected = true;
                    } else if (option3.getGlobalBounds().contains(mousePosF)) {
                        selectedOption = Option::Turn;
                        optionSelected = true;
                    }
                }
            }
        }

        window.clear(sf::Color::Red);
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);
        window.display();
    }

    window.close();
    return selectedOption;
}

