//
// Created by Cristian Andrei Visan on 07.11.2025.
//

#include "Computer.h"

#include <random>
#include <algorithm>

#include "buttonsInOrder.h"
#include "tagZones.h"

Computer::Computer(){
    this->puzzleInProgress = false;
}

Computer::~Computer() = default;

std::string Computer::getKey() {
    std::string key;
    key.resize(16);
    for (int i = 0; i < 10; i++) {
        key[i] = '0' + i;
    }
    for (int i = 0; i < 6; i++) {
        key[10 + i] = 'a' + i;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(key.begin(), key.end(), gen);
    return key;
}

void Computer::timerThread(Puzzle &puzzle) {
    (void)puzzle;
}

void Computer::generatePuzzle(int milestone) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    switch (dist(gen) % 2) {
        case 0:
            newPuzzle = new buttonsInOrder(milestone);
            break;
        case 1:
            newPuzzle = new tagZones(milestone);
            break;
        default: ;
    }

    newPuzzle->setSolved(false);
    newPuzzle->setTimeUp(false);



}

void Computer::eventLoop(int milestone, Player& player) {
        for (int i = 0; i < milestone; i++) {
            generatePuzzle(milestone);

            std::cout << "Puzzle-ul pe care trebuie sa-l rezolvi este: \n" << *newPuzzle << std::endl;
            newPuzzle->setAnswer(newPuzzle->getAnswer());


            if (newPuzzle->checkAnswer() == 1) {
                std::cout << "You have solved this puzzle. You have been awarded " << newPuzzle->getPoints() << " points." << std::endl;
                player.setPoints(player.getPoints() + newPuzzle->getPoints());
            } else {
                std::cout << "You have failed to solve the puzzle.";

            }
        }
}
