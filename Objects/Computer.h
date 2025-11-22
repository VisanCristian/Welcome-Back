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
    Computer(const Player& player);
    ~Computer();


    void generatePuzzle(int milestone);
    void eventLoop(int milestone);
    std::string buyKey(Player& player);
    static void timerThread(Puzzle &puzzle);

};


#endif //OOP_COMPUTER_H