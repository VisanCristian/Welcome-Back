#ifndef OOP_COMPUTER_H
#define OOP_COMPUTER_H

#include "Player.h"
#include "Puzzle.h"
#include "Result.h"
#include "GameError.h"
#include "ConstructorError.h"

#include <memory>

class Computer {
    std::shared_ptr<Puzzle> newPuzzle;

public:
    Computer();
    Computer(const Computer& other);
    ~Computer();

    Computer& operator=(Computer other);
    friend void swap(Computer& a, Computer& b) noexcept;

    Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError> generatePuzzle(int milestone);
    void eventLoop(int milestone, Player& player, int& wrongChoice);
    static Result<std::string, GameError> getKey();
};

#endif
