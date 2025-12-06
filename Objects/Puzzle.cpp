//
// Created by visan on 11/1/25.
//

#include "Puzzle.h"
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;

Puzzle::Puzzle(){
    this->solved = false;
    this->timeUp = false;
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
