//
// Created by Cristian Andrei Visan on 07.11.2025.
//

#ifndef OOP_COMPUTER_H
#define OOP_COMPUTER_H
#include "Player.h"
#include "Puzzle.h"
#include "GameErrors.h"

#include <memory>

class Computer {
    Player player;
    std::shared_ptr<Puzzle> newPuzzle;

public:
    Computer();
    Computer(const Computer& other);
    ~Computer();

    Computer& operator=(Computer other);
    friend void swap(Computer& a, Computer& b) noexcept;

    Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError> generatePuzzle(int milestone);
    void eventLoop(int milestone, Player& player);
    static Result<std::string, GameError> getKey();
    static void timerThread(Puzzle &puzzle);

};


#endif //OOP_COMPUTER_H
