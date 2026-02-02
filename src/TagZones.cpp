#include "headers/TagZones.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <stack>
#include <cmath>
#include <SFML/Graphics.hpp>

void TagZones::generatePuzzle() {
    size_t puzzleSize = userAnswer.size();
    puzzle.resize(puzzleSize);
    for (int i = 0; i < static_cast<int>(puzzleSize); i++) {
        puzzle[i] = i;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    for (int i = 0; i < static_cast<int>(puzzleSize); i++) {
        puzzle[i] = (dist(gen) == 0) ? 0 : -1;
    }
}

std::vector<int> TagZones::getUserInput() {
    const int windowWidth = 800;
    const int windowHeight = 800;
    const int side = static_cast<int>(std::sqrt(static_cast<double>(userAnswer.size())));
    const int cellSize = std::min(700 / side, 100);
    const int gridSize = side * cellSize;
    const int startX = (windowWidth - gridSize) / 2;
    const int startY = (windowHeight - gridSize) / 2;

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)), "Tag Zones");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("assets/fonts/arial.ttf")) {
        userAnswer = correctAnswer;
        return userAnswer;
    }

    std::vector<sf::RectangleShape> cells;
    std::vector<sf::Text> cellTexts;
    std::vector<int> currentTags = puzzle;
    int currentZoneId = 2;

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize - 2), static_cast<float>(cellSize - 2)));
            cell.setPosition(sf::Vector2f(static_cast<float>(startX + j * cellSize + 1),
                                          static_cast<float>(startY + i * cellSize + 1)));
            if (puzzle[i * side + j] == 0) {
                cell.setFillColor(sf::Color(100, 100, 100));
            } else {
                cell.setFillColor(sf::Color::White);
            }
            cell.setOutlineColor(sf::Color::Black);
            cell.setOutlineThickness(1.0f);
            cells.push_back(cell);

            sf::Text text(font);
            if (puzzle[i * side + j] == -1) {
                text.setString("?");
            } else {
                text.setString("");
            }
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(sf::Vector2f(textBounds.position.x + textBounds.size.x / 2.0f,
                                        textBounds.position.y + textBounds.size.y / 2.0f));
            text.setPosition(sf::Vector2f(static_cast<float>(startX + j * cellSize + cellSize / 2),
                                          static_cast<float>(startY + i * cellSize + cellSize / 2)));
            cellTexts.push_back(text);
        }
    }

    sf::Text instructions(font);
    instructions.setString("Click on ? cells to tag zones. Press ENTER when done.");
    instructions.setCharacterSize(18);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(sf::Vector2f(20.0f, 20.0f));

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                userAnswer = currentTags;
                return userAnswer;
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    window.close();
                }
            }

            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButton->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(static_cast<float>(mouseButton->position.x),
                                         static_cast<float>(mouseButton->position.y));

                    for (int i = 0; i < side; i++) {
                        for (int j = 0; j < side; j++) {
                            int index = i * side + j;
                            if (puzzle[index] == -1 && cells[index].getGlobalBounds().contains(mousePos)) {
                                std::stack<std::pair<int,int>> toTag;
                                toTag.push({i, j});

                                while (!toTag.empty()) {
                                    auto [x, y] = toTag.top();
                                    toTag.pop();

                                    int pos = x * side + y;
                                    if (currentTags[pos] != -1) {
                                        continue;
                                    }

                                    currentTags[pos] = currentZoneId;
                                    cellTexts[pos].setString(std::to_string(currentZoneId));
                                    cells[pos].setFillColor(sf::Color(50 + currentZoneId * 30, 150, 200));

                                    if (x > 0 && currentTags[(x - 1) * side + y] == -1)
                                        toTag.push({x - 1, y});
                                    if (x < side - 1 && currentTags[(x + 1) * side + y] == -1)
                                        toTag.push({x + 1, y});
                                    if (y > 0 && currentTags[x * side + (y - 1)] == -1)
                                        toTag.push({x, y - 1});
                                    if (y < side - 1 && currentTags[x * side + (y + 1)] == -1)
                                        toTag.push({x, y + 1});
                                }

                                currentZoneId++;
                                goto event_loop_end;
                            }
                        }
                    }
                    event_loop_end:;
                }
            }
        }

        window.clear(sf::Color::Black);
        for (size_t i = 0; i < cells.size(); i++) {
            window.draw(cells[i]);
            window.draw(cellTexts[i]);
        }
        window.draw(instructions);
        window.display();
    }

    userAnswer = currentTags;
    return userAnswer;
}

void TagZones::setAnswer(const std::vector<int> &answer) {
    this->userAnswer = answer;
}

void TagZones::setCorrectAnswer() {
    std::stack<std::pair<int,int>> posToCount;
    correctAnswer = puzzle;
    int componentId = 2;

    const int side = static_cast<int>(std::sqrt(static_cast<double>(userAnswer.size())));

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            if (correctAnswer[i * side + j] == -1) {
                posToCount.push({i, j});
                while (!posToCount.empty()) {
                    auto [x, y] = posToCount.top();
                    posToCount.pop();

                    correctAnswer[x * side + y] = componentId;

                    if (x > 0 && correctAnswer[(x - 1) * side + y] == -1)
                        posToCount.push({x - 1, y});
                    if (x < side - 1 && correctAnswer[(x + 1) * side + y] == -1)
                        posToCount.push({x + 1, y});
                    if (y > 0 && correctAnswer[x * side + (y - 1)] == -1)
                        posToCount.push({x, y - 1});
                    if (y < side - 1 && correctAnswer[x * side + (y + 1)] == -1)
                        posToCount.push({x, y + 1});
                }
                componentId++;
            }
        }
    }
}

bool TagZones::checkAnswer() const {
    return userAnswer == correctAnswer;
}

std::unique_ptr<Puzzle> TagZones::clone() const {
    return std::make_unique<TagZones>(*this);
}

void TagZones::print(std::ostream& os) const {
    os << "Puzzle: \n";
    int side = static_cast<int>(std::sqrt(static_cast<double>(userAnswer.size())));
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            os << puzzle[i * side + j] << " ";
        }
        os << std::endl;
    }
    os << std::endl;
    os << "In order to solve this puzzle you need to tag each zone such that in the end, the biggest tag is the number of independent zones" << std::endl;
    os << "2 blocks form a zone if they are adjacent (up down, left right)" << std::endl;
    os << "\n";
}

std::ostream& operator<<(std::ostream& os, const TagZones& obj) {
    obj.print(os);
    return os;
}
