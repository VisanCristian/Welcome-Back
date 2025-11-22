//
// Created by visan on 11/2/25.
//

#include "tagZones.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <iostream>
#include <stack>



void tagZones::generatePuzzle() {
    puzzle.resize(3 * 3);
    for (int i = 0; i < 3; i++) {
        puzzle[i] = i;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    for (int i = 0; i < 3 * 3; i++) {
        puzzle[i] = (dist(gen) == 0) ? 0 : -1;
    }

}

std::vector<int> tagZones::getUserInput() {
    for (int i = 0; i < 3 * 3; i++) {
        std::cin >> userAnswer[i];
    }
    return userAnswer;
}

std::vector<int> tagZones::getAnswer() {
    std::ifstream fin("rightAnswears.txt");
    std::vector<int> Answer(3 * 3, -1);
    for (int i = 0; i < 3 * 3; i++) {
        fin >> Answer[i];
    }
    return Answer;
}


void tagZones::setAnswer(const std::vector<int> &Answer) {
    std::vector<int> wrong(9, -1);
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
    int comp = 2; int m = 3;
    std::ofstream fout("rightAnswears.txt");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (correctAnswer[i * m + j] == -1) {
                posToCount.push({i, j});
                while (!posToCount.empty()) {
                    auto [x, y] = posToCount.top();
                    posToCount.pop();

                    correctAnswer[x * m + y] = comp;

                    // Check neighbors with bounds
                    if (x > 0 && correctAnswer[(x - 1) * m + y] == -1)
                        posToCount.push({x - 1, y});
                    if (x < m - 1 && correctAnswer[(x + 1) * m + y] == -1)
                        posToCount.push({x + 1, y});
                    if (y > 0 && correctAnswer[x * m + (y - 1)] == -1)
                        posToCount.push({x, y - 1});
                    if (y < m - 1 && correctAnswer[x * m + (y + 1)] == -1)
                        posToCount.push({x, y + 1});
                }
                comp++;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            fout << correctAnswer[i * m + j] << " ";
        }
        fout << std::endl;
    }
}

bool tagZones::checkAnswer() const {
    return userAnswer == correctAnswer;
}

std::ostream& operator<<(std::ostream& os, const tagZones& obj) {
    os << "Puzzle: \n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            os << obj.puzzle[i * 3 + j] << " ";
        }
        os << std::endl;
    }
    os << std::endl;

    os << "Puzzle Key: ";
    for (const auto& ch : obj.key) {
        os << ch;
    }
    os << "\n";
    os << "In order to solve this puzzle you need to tag each zone such that in the end, the biggest tag is the number of independent zones" << std::endl;
    os << "2 blocks form a zone if they are adjacent (up down, left right)" << std::endl;
    os << "User Answer: \n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            os << obj.userAnswer[i * 3 + j] << " ";
        }
        os << std::endl;
    }
    os << "\n";

    return os;
}
