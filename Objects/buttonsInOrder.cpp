//
// Created by visan on 11/2/25.
//

#include "buttonsInOrder.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>

void buttonsInOrder::generatePuzzle() {
    puzzle.resize(10, -1);

    for (int i = 0; i < 10; i++) {
        puzzle[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::ranges::shuffle(puzzle, gen);

    std::ofstream fout("rightAnswears.txt");
    for (int i = 0; i < 10; i++) {
        fout << puzzle[i] << " ";
    }
    fout << std::endl;
}

std::vector<int> buttonsInOrder::getUserInput() {
    for (int i = 0; i < 10; i++) {
        std::cin >> userAnswer[i];
    }
    return userAnswer;
}

void buttonsInOrder::setCorrectAnswer() {
    this->correctAnswer = puzzle;
}

std::vector<int> buttonsInOrder::getAnswer() {
    std::ifstream fin("rightAnswears.txt");
    std::vector<int> Answer(10, -1);
    for (int i = 0; i < 10; i++) {
        fin >> Answer[i];
    }
    return Answer;
}


void buttonsInOrder::setAnswer(const std::vector<int> &Answer) {
    std::vector<int> wrong(10, -1);
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

std::ostream& operator<<(std::ostream& os, const buttonsInOrder& obj) {
    os << "Puzzle: \n";
    for (int i = 0; i < 10; i++) {
        os << obj.puzzle[i] << " ";
    }
    os << std::endl;

    return os;
}
