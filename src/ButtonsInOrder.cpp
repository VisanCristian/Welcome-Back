#include "../headers/ButtonsInOrder.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

void ButtonsInOrder::generatePuzzle() {
    size_t puzzleSize = userAnswer.size();
    puzzle.resize(puzzleSize, -1);

    for (int i = 0; i < static_cast<int>(puzzleSize); i++) {
        puzzle[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(puzzle, gen);
}

std::vector<int> ButtonsInOrder::getUserInput() {
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int buttonSize = 80;
    const int padding = 20;
    const int maxButtonsPerRow = 7;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)), "Buttons In Order");
    window.setFramerateLimit(60);

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    std::vector<int> clickedOrder;

    sf::Font font;
    if (!font.openFromFile("assets/fonts/arial.ttf")) {
        for (size_t i = 0; i < puzzle.size(); i++) {
            clickedOrder.push_back(static_cast<int>(i));
        }
        userAnswer = clickedOrder;
        return clickedOrder;
    }

    const int numButtons = static_cast<int>(puzzle.size());
    const int buttonsPerRow = std::min(numButtons, maxButtonsPerRow);
    const int numRows = (numButtons + buttonsPerRow - 1) / buttonsPerRow;

    const int totalWidth = buttonsPerRow * buttonSize + (buttonsPerRow - 1) * padding;
    const int totalHeight = numRows * buttonSize + (numRows - 1) * padding;
    const int startX = (windowWidth - totalWidth) / 2;
    const int startY = (windowHeight - totalHeight) / 2;

    for (int i = 0; i < numButtons; i++) {
        const int row = i / buttonsPerRow;
        const int col = i % buttonsPerRow;
        const int x = startX + col * (buttonSize + padding);
        const int y = startY + row * (buttonSize + padding);

        sf::RectangleShape button(sf::Vector2f(static_cast<float>(buttonSize), static_cast<float>(buttonSize)));
        button.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
        button.setFillColor(sf::Color::White);
        button.setOutlineColor(sf::Color::Blue);
        button.setOutlineThickness(2.0f);
        buttons.push_back(button);

        sf::Text text(font);
        text.setString(std::to_string(puzzle[i]));
        text.setCharacterSize(32);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(sf::Vector2f(textBounds.position.x + textBounds.size.x / 2.0f,
                                     textBounds.position.y + textBounds.size.y / 2.0f));
        text.setPosition(sf::Vector2f(static_cast<float>(x + buttonSize / 2),
                                       static_cast<float>(y + buttonSize / 2)));
        buttonTexts.push_back(text);
    }

    std::vector<bool> clicked(numButtons, false);

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                for (size_t i = 0; i < puzzle.size(); i++) {
                    clickedOrder.push_back(static_cast<int>(i));
                }
                userAnswer = clickedOrder;
                return clickedOrder;
            }

            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButton->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(static_cast<float>(mouseButton->position.x),
                                         static_cast<float>(mouseButton->position.y));

                    for (int i = 0; i < numButtons; i++) {
                        if (!clicked[i] && buttons[i].getGlobalBounds().contains(mousePos)) {
                            clicked[i] = true;
                            buttons[i].setFillColor(sf::Color::Green);
                            clickedOrder.push_back(puzzle[i]);

                            if (static_cast<int>(clickedOrder.size()) == numButtons) {
                                window.close();
                            }
                            break;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        for (size_t i = 0; i < buttons.size(); i++) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
        window.display();
    }

    userAnswer = clickedOrder;
    return clickedOrder;
}

void ButtonsInOrder::setCorrectAnswer() {
    correctAnswer.resize(puzzle.size());
    for (size_t i = 0; i < puzzle.size(); i++) {
        correctAnswer[i] = static_cast<int>(i);
    }
}

void ButtonsInOrder::setAnswer(const std::vector<int> &answer) {
    this->userAnswer = answer;
}

bool ButtonsInOrder::checkAnswer() const {
    return userAnswer == correctAnswer;
}

std::unique_ptr<Puzzle> ButtonsInOrder::clone() const {
    return std::make_unique<ButtonsInOrder>(*this);
}

void ButtonsInOrder::print(std::ostream& os) const {
    os << "Puzzle: \n";
    for (int i = 0; i < static_cast<int>(puzzle.size()); i++) {
        os << puzzle[i] << " ";
    }
    os << std::endl;
}

std::ostream& operator<<(std::ostream& os, const ButtonsInOrder& obj) {
    obj.print(os);
    return os;
}
