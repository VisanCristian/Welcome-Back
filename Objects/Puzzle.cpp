//
// Created by visan on 11/1/25.
//

#include "Puzzle.h"
#include <random>
#include <algorithm>
#include <fstream>

void Puzzle::generatePuzzle() {
    puzzle.resize(10, -1);
    for (int i = 0; i < 10; i++) {
        puzzle[i] = i;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(puzzle, gen);

    std::ofstream fout("tastatura.txt");
    for (int i = 0; i < 10; i++) {
        fout << puzzle[i] << " ";
    }
    fout << std::endl;
}

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

Puzzle::Puzzle(const std::string& type) : puzzleType(type){
    this->solved = false;
    generatePuzzle();
    generateKey();
}

Puzzle::Puzzle(const Puzzle& other) {
    this->puzzle = other.puzzle;
    this->puzzleType = other.puzzleType;
    this->key = other.key;
    this->solved = other.solved.load();
    this->timeUp = other.timeUp.load();
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
    os << "User Answer: ";
    for (unsigned long int i = 0; i < obj.userAnswer.size(); i++) {
        os << obj.userAnswer[i] << " ";
    }
    os << "\n";

    return os;
}

Puzzle& Puzzle::operator=(const Puzzle& other) {
    if (this != &other) {
        this->puzzle = other.puzzle;
        this->puzzleType = other.puzzleType;
        this->key = other.key;
        this->solved = other.solved.load();
        this->timeUp = other.timeUp.load();
    }
    return *this;
}

std::vector<int> Puzzle::getAnswer() {
    std::ifstream fin("tastatura.txt");
    std::vector<int> Answer(10, -1);
    for (int i = 0; i < 10; i++) {
        fin >> Answer[i];
    }
    return Answer;
}

void Puzzle::setAnswer(const std::vector<int>& Answer) {
    this->userAnswer = Answer;
}

int Puzzle::getTimeLimit() const {
    return puzzleTimeLimits.at(puzzleType);
}

void Puzzle::setSolved(const bool status) {
    this->solved = status;
}

bool Puzzle::getSolved() const {
    return this->solved;
}

void Puzzle::setTimeUp(const bool status) {
    this->timeUp = status;
}
bool Puzzle::getTimeUp() const {
    return this->timeUp;
}

[[nodiscard]] bool Puzzle::checkAnswer() const {
    return userAnswer == puzzle;
}
