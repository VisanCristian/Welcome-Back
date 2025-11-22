//
// Created by Cristian Andrei Visan on 07.11.2025.
//

#include "Computer.h"

#include <random>

#include "buttonsInOrder.h"
#include "tagZones.h"

Computer::Computer(const Player &player) : player(player) {
    this->puzzleInProgress = false;
}

Computer::~Computer() = default;

void Computer::generatePuzzle(int milestone) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    switch (dist(gen) % 2) {
        case 0:
            newPuzzle = new buttonsInOrder(milestone);
        case 1:
            newPuzzle = new tagZones(milestone);
        default: ;
    }

    newPuzzle->setSolved(false);
    newPuzzle->setTimeUp(false);

    std::vector<int> userAnswer;
    std::cout << newPuzzle;


    if (newPuzzle->checkAnswer() == 0) {
        puzzleInProgress = false;
    }else {
        newPuzzle->setSolved(true);
        std::cout << "You have solved the puzzle. You have been awarded" << newPuzzle->getPoints() << " points." << std::endl;
    }
}

void Computer::eventLoop(int milestone) {
    generatePuzzle(milestone);
    newPuzzle->setAnswer(getUserInput());

    if (newPuzzle->checkAnswer() == 1) {
        std::cout << "You have solved this puzzle. You have been awarded " << newPuzzle->getPoints() << " points." << std::endl;
        player.setPoints(player.getPoints() + newPuzzle->getPoints());
        player.addKey(newPuzzle->getKey());
    }
}