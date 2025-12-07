//
// Created by visan on 11/2/25.
//

#include "tagZones.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <stack>
#include <cmath>
#include "GameErrors.h"



void tagZones::generatePuzzle() {
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

std::vector<int> tagZones::getUserInput() {
    userAnswer = correctAnswer;
    return userAnswer;
}

void tagZones::setAnswer(const std::vector<int> &Answer) {
    std::vector<int> wrong(Answer.size(), -1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 5);

    if (dist(gen) == 2) {
        this->userAnswer = wrong;
        return;
    }
    this->userAnswer = Answer;
}

void tagZones::setCorrectAnswer() {
    std::stack<std::pair<int,int>> posToCount;
    correctAnswer = puzzle;
    int comp = 2;

    const int side = static_cast<int>(std::sqrt(static_cast<double>(userAnswer.size())));

    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            if (correctAnswer[i * side + j] == -1) {
                posToCount.push({i, j});
                while (!posToCount.empty()) {
                    auto [x, y] = posToCount.top();
                    posToCount.pop();

                    correctAnswer[x * side + y] = comp;

                    if (x > 0 && correctAnswer[(x - 1) * side + y] == -1)
                        posToCount.push({x - 1, y});
                    if (x < side - 1 && correctAnswer[(x + 1) * side + y] == -1)
                        posToCount.push({x + 1, y});
                    if (y > 0 && correctAnswer[x * side + (y - 1)] == -1)
                        posToCount.push({x, y - 1});
                    if (y < side - 1 && correctAnswer[x * side + (y + 1)] == -1)
                        posToCount.push({x, y + 1});
                }
                comp++;
            }
        }
    }
}

bool tagZones::checkAnswer() const {
    return userAnswer == correctAnswer;
}

std::unique_ptr<Puzzle> tagZones::clone() const {
    return std::make_unique<tagZones>(*this);
}

void tagZones::print(std::ostream& os) const {
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

std::ostream& operator<<(std::ostream& os, const tagZones& obj) {
    obj.print(os);
    return os;
}
