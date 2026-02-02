#ifndef OOP_PUZZLEFACTORY_H
#define OOP_PUZZLEFACTORY_H

#include <memory>
#include <string>
#include "headers/Puzzle.h"

class PuzzleFactory {
public:
    static std::shared_ptr<Puzzle> createPuzzle(const std::string& tier);
};

#endif //OOP_PUZZLEFACTORY_H
