//
// Created by visan on 11/2/25.
//

#include "buttonsInOrder.h"
#include <random>
#include <algorithm>
#include <iostream>
#include "GameErrors.h"

void buttonsInOrder::generatePuzzle() {
    size_t puzzleSize = userAnswer.size();
    puzzle.resize(puzzleSize, -1);

    for (int i = 0; i < static_cast<int>(puzzleSize); i++) {
        puzzle[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(puzzle, gen);
}

std::vector<int> buttonsInOrder::getUserInput() {
    for (int i = 0; i < 10; i++) {
        if (!(std::cin >> userAnswer[i])) {
            throw GameError("buttonsInOrder::getUserInput - failed to read user input");
        }
    }
    return userAnswer;
}

void buttonsInOrder::setCorrectAnswer() {
    this->correctAnswer = puzzle;
}

std::vector<int> buttonsInOrder::getAnswer(){
    return correctAnswer;
}


void buttonsInOrder::setAnswer(const std::vector<int> &Answer) {
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

bool buttonsInOrder::checkAnswer() const {
    return userAnswer == correctAnswer;
}

std::unique_ptr<Puzzle> buttonsInOrder::clone() const {
    return std::make_unique<buttonsInOrder>(*this);
}

void buttonsInOrder::print(std::ostream& os) const {
    os << "Puzzle: \n";
    for (int i = 0; i < static_cast<int>(puzzle.size()); i++) {
        os << puzzle[i] << " ";
    }
    os << std::endl;
}

std::ostream& operator<<(std::ostream& os, const buttonsInOrder& obj) {
    obj.print(os);
    return os;
}
