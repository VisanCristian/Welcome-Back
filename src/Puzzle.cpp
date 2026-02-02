#include "headers/Puzzle.h"
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;

Puzzle::Puzzle(){
    this->solved = false;
    this->timeUp = false;
}

Puzzle::Puzzle(const Puzzle& other)
    : points(other.points),
      puzzle(other.puzzle),
      userAnswer(other.userAnswer),
      correctAnswer(other.correctAnswer) {
    solved.store(other.solved.load());
    timeUp.store(other.timeUp.load());
}

Puzzle& Puzzle::operator=(const Puzzle& other) {
    if (this != &other) {
        points = other.points;
        puzzle = other.puzzle;
        userAnswer = other.userAnswer;
        correctAnswer = other.correctAnswer;
        solved.store(other.solved.load());
        timeUp.store(other.timeUp.load());
    }
    return *this;
}

int Puzzle::getPoints() const {
    return points;
}

std::ostream& operator<<(std::ostream& os, const Puzzle& obj) {
    obj.print(os);
    return os;
}

void Puzzle::setTimeUp(bool status) {
    timeUp.store(status);
}
