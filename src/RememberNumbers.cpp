#include "headers/RememberNumbers.h"
#include <vector>
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

RememberNumbers::RememberNumbers(int timeLimit, int points, int size) {
    this->timeLimit = timeLimit;
    this->points = points;
    userAnswer.resize(size);
    RememberNumbers::generatePuzzle();
    setCorrectAnswer();
}

std::ostream& operator<<(std::ostream& os, const RememberNumbers& obj) {
    obj.print(os);
    return os;
}

std::vector<int> RememberNumbers::getUserInput() {
    const int windowWidth = 800;
    const int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)), "Remember Numbers");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("assets/fonts/arial.ttf")) {
        // Fallback if font missing, print to console
        std::cout << "Memorize these numbers: ";
        for (int num : puzzle) {
            std::cout << num << " ";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << std::endl;
    } else {
        sf::Text text(font);
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::White);

        for (int num : puzzle) {
            window.clear(sf::Color::Black);
            text.setString(std::to_string(num));
            
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(sf::Vector2f(textBounds.position.x + textBounds.size.x / 2.0f,
                                        textBounds.position.y + textBounds.size.y / 2.0f));
            text.setPosition(sf::Vector2f(static_cast<float>(windowWidth) / 2.0f,
                                          static_cast<float>(windowHeight) / 2.0f));
            
            window.draw(text);
            window.display();

            // Handle events to keep window responsive (and allow closing)
            auto startTime = std::chrono::steady_clock::now();
            while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(1)) {
                if (const auto event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>()) {
                        window.close();
                        // If closed early, we can return what we have or empty, 
                        // but better to just stop showing.
                        goto ask_input;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
        window.close();
    }

ask_input:
    std::vector<int> input;
    std::cout << "Enter the numbers you saw, separated by spaces: ";
    for (size_t i = 0; i < puzzle.size(); ++i) {
        int val;
        if (std::cin >> val) {
            input.push_back(val);
        } else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            break;
        }
    }
    
    // Consume remaining newline if any
    std::cin.ignore(10000, '\n');

    userAnswer = input;
    return userAnswer;
}

std::unique_ptr<Puzzle> RememberNumbers::clone() const {
    return std::make_unique<RememberNumbers>(*this);
}

void RememberNumbers::generatePuzzle() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 20);

    puzzle.clear();
    for (int j = 0; j < static_cast<int>(userAnswer.size()); j++) {
         puzzle.push_back(dist(gen));
    }
}

void RememberNumbers::setCorrectAnswer() {
    correctAnswer = puzzle;
}

void RememberNumbers::print(std::ostream& os) const {
    os << "What are the numbers? (Watch the window!) \n";
}

bool RememberNumbers::checkAnswer() const {
    return userAnswer == correctAnswer;
}

void RememberNumbers::setAnswer(const std::vector<int>& answer) {
    this->userAnswer = answer;
}

int RememberNumbers::getTimeLimit() const { return this->timeLimit; };