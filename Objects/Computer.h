//
// Created by Cristian Andrei Visan on 07.11.2025.
//

#ifndef OOP_COMPUTER_H
#define OOP_COMPUTER_H
#include "Player.h"
#include "Puzzle.h"


class Computer {
    bool puzzleInProgress;
    Player player;
    Puzzle*  newPuzzle = nullptr;

public:
    Computer();
    ~Computer();


    void generatePuzzle(int milestone);
    void eventLoop(int milestone, Player& player);
    std::string getKey();
    static void timerThread(Puzzle &puzzle);

};


#endif //OOP_COMPUTER_H