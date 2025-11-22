//
// Created by visan on 11/1/25.
//

#include "Puzzle.h"
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;

void Puzzle::generateKey() {
    key.resize(16);
    for (int i = 0; i < 10; i++) {
        key[i] = '0' + i;
    }
    for (int i = 0; i < 6; i++) {
        key[10 + i] = 'a' + i;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(key, gen);
}

Puzzle::Puzzle(){
    this->solved = false;
    this->timeUp = false;
    generateKey();
}

int Puzzle::getPoints() const {
    return points;
}

std::ostream& operator<<(std::ostream& os, const Puzzle& obj) {
    os << "Puzzle: \n";
    for (int i = 0; i < 10; i++) {
        os << obj.puzzle[i] << " ";
    }
    os << std::endl;

    os << "Puzzle Key: ";
    for (const auto& ch : obj.key) {
        os << ch;
    }
    os << "\n";
    os << "User Answer: \n";
    for (unsigned long int i = 0; i < obj.userAnswer.size(); i++) {
        os << obj.userAnswer[i] << " ";
    }
    os << "\n";

    return os;
}

void Puzzle::setSolved(const bool status) {
    solved.store(status);
}

bool Puzzle::getSolved() const {
    return solved.load();
}

void Puzzle::setTimeUp(const bool status) {
    timeUp.store(status);
}
bool Puzzle::getTimeUp() const {
    return timeUp.load();
}
