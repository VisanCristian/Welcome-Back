#include "headers/PuzzleFactory.h"
#include "headers/ButtonsInOrder.h"
#include "headers/TagZones.h"
#include "headers/RememberNumbers.h"
#include "headers/ConstructorError.h"
#include <random>

std::shared_ptr<Puzzle> PuzzleFactory::createPuzzle(const std::string& tier) {
    if (tier == "T1") {
        auto puzzle = std::make_shared<ButtonsInOrder>(60, 100, 15);
        puzzle->setTimeUp(false);
        return puzzle;
    } else if (tier == "T2") {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, 100);
        std::shared_ptr<Puzzle> puzzle;
        if (dist(gen) % 3 == 0) {
            puzzle = std::make_shared<ButtonsInOrder>(60, 200, 30);
        } else if (dist(gen) % 3 == 1) {
            puzzle = std::make_shared<TagZones>(60, 200, 49);
        } else {
            puzzle = std::make_shared<RememberNumbers>(60, 200, 5);
        }
        puzzle->setTimeUp(false);
        return puzzle;
    } else if (tier == "T3") {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, 100);
        std::shared_ptr<Puzzle> puzzle;
        if (dist(gen) % 4 == 0) {
            puzzle = std::make_shared<ButtonsInOrder>(60, 300, 50);
        } else if (dist(gen) % 4 == 1) {
            puzzle = std::make_shared<TagZones>(60, 300, 100);
        } else if (dist(gen) % 4 == 2){
            puzzle = std::make_shared<RememberNumbers>(60, 300, 10);
        } else {
            puzzle = std::make_shared<RememberNumbers>(60, 300, 7);
        }
        puzzle->setTimeUp(false);
        return puzzle;
    } else {
        throw ConstructorError("PuzzleFactory::createPuzzle - invalid tier token");
    }
}
