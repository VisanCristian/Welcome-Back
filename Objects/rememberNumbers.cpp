#include "rememberNumbers.h"
#include <vector>
#include <random>
#include <iostream>

rememberNumbers::rememberNumbers(const int timelimit, const int points, const int size) {
    this->timeLimit = timelimit;
    this->points = points;
    userAnswer.resize(size);
    rememberNumbers::generatePuzzle();
    setCorrectAnswer();
}

std::ostream& operator<<(std::ostream& os, const rememberNumbers& obj) {
    obj.print(os);
    return os;
}

std::vector<int> rememberNumbers::getUserInput() {
    std::vector<int> Answer(userAnswer.size());

    for (int i = 0; i < static_cast<int>(userAnswer.size()); i++) {
        if (!(std::cin >> Answer[i])) {
            throw GameError("rememberNumbers::getUserInput - failed to read user input");
        }
    }
    return Answer;
}

std::unique_ptr<Puzzle> rememberNumbers::clone() const {
    return std::make_unique<rememberNumbers>(*this);
}


void rememberNumbers::generatePuzzle() {
    for (int i = 0; i < 3; i++) {
        std::cout << "Round #" << i + 1 << std::endl;
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, 20);
    
        for (int i = 0; i < static_cast<int>(userAnswer.size()); i++) {
            puzzle.push_back(dist(gen));
        }   
    }
    userAnswer = getUserInput();
}

void rememberNumbers::setCorrectAnswer() {
    for (int i = 0; i < static_cast<int>(userAnswer.size()); i++) {
        correctAnswer.push_back(puzzle[i]);
    }
}

void rememberNumbers::print(std::ostream& os) const {
    os << "What are the numbers? \n";
}

bool rememberNumbers::checkAnswer() const {
    return userAnswer == correctAnswer;
}

void rememberNumbers::setAnswer(const std::vector<int>& Answer) { 
    std::vector<int> wrong(Answer.size(), -1);

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 100);
    if (dist(gen) % 7 == 0) {
        this->userAnswer = wrong;
    }
    this->userAnswer = Answer; 
}


int rememberNumbers::getTimeLimit() const { return this->timeLimit; };




