//
// Created by Cristian Andrei Visan on 07.11.2025.
//

#include "Computer.h"

#include <random>
#include <algorithm>
#include <fstream>
#include <utility>

#include "buttonsInOrder.h"
#include "tagZones.h"
#include "PathFinding.h"

Computer::Computer(){
    this->puzzleInProgress = false;
}

Computer::Computer(const Computer& other)
    : puzzleInProgress(other.puzzleInProgress),
      player(other.player),
      newPuzzle(other.newPuzzle
                ? std::shared_ptr<Puzzle>(other.newPuzzle->clone().release())
                : nullptr) {}

Computer::~Computer() = default;

void swap(Computer& a, Computer& b) noexcept {
    using std::swap;
    swap(a.puzzleInProgress, b.puzzleInProgress);
    swap(a.player, b.player);
    swap(a.newPuzzle, b.newPuzzle);
}

Computer& Computer::operator=(Computer other) {
    swap(*this, other);
    return *this;
}

Result<std::string, GameError> Computer::getKey() const {
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
    return Result<std::string, GameError>::OkResult(key);
}

void Computer::timerThread(Puzzle &puzzle) {
    (void)puzzle;
}

Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError> Computer::generatePuzzle(int milestone) {

    std::ifstream fin("assets/PuzzleDecks");
    if (!fin) {
        return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(
                ConstructorError("Computer::generatePuzzle - could not open PuzzleDecks for reading"));
    }

    const std::string structure = "M" + std::to_string(milestone);
    std::vector<std::shared_ptr<Puzzle>> puzzles;
    std::string tier;

    while (tier != structure) {
        if (!(fin >> tier)) {
            return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(
                    ConstructorError("Computer::generatePuzzle - failed while reading from PuzzleDecks"));
        }
    }

    for (int i = 0; i < 7; i++) {
        if (!(fin >> tier)) {
            return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(
                    ConstructorError("Computer::generatePuzzle - not enough tier entries for milestone"));
        }

        if (tier == "T1") {
            newPuzzle = std::make_shared<buttonsInOrder>(60, 100, 15);
            newPuzzle->setSolved(false);
            newPuzzle->setTimeUp(false);
            puzzles.push_back(newPuzzle);
        } else if (tier == "T2") {
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<int> dist(1, 100);
            if (dist(gen) % 3 == 0) {
                newPuzzle = std::make_shared<buttonsInOrder>(60, 200, 30);
            } else if (dist(gen) % 3 == 1) {
                newPuzzle = std::make_shared<tagZones>(60, 200, 49);
            } else {
                newPuzzle = std::make_shared<PathFinding>(60, 200, 20);
            }
            newPuzzle->setSolved(false);
            newPuzzle->setTimeUp(false);
            puzzles.push_back(newPuzzle);
        } else if (tier == "T3") {
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<int> dist(1, 100);
            if (dist(gen) % 3 == 0) {
                newPuzzle = std::make_shared<buttonsInOrder>(60, 300, 50);
            } else if (dist(gen) % 3 == 1) {
                newPuzzle = std::make_shared<tagZones>(60, 300, 100);
            } else {
                newPuzzle = std::make_shared<PathFinding>(60, 300, 20);
            }
            newPuzzle->setSolved(false);
            newPuzzle->setTimeUp(false);
            puzzles.push_back(newPuzzle);

            if (dist(gen) % 2 == 0) {
                newPuzzle = std::make_shared<tagZones>(60, 300, 100);
            } else {
                newPuzzle = std::make_shared<PathFinding>(60, 300, 25);
            }
            newPuzzle->setSolved(false);
            newPuzzle->setTimeUp(false);
            puzzles.push_back(newPuzzle);
        } else {
            return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(
                    ConstructorError("Computer::generatePuzzle - invalid tier token in PuzzleDecks"));
        }
    }

    if (puzzles.empty()) {
        return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(
                ConstructorError("Computer::generatePuzzle - no puzzles generated for milestone"));
    }

    std::mt19937 gen(std::random_device{}());
    std::shuffle(puzzles.begin(), puzzles.end(), gen);

    return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::OkResult(puzzles);
}

void Computer::eventLoop(int milestone, Player& player) {
    auto puzzleResult = generatePuzzle(milestone);
    if (!puzzleResult.isOk()) {
        throw puzzleResult.getErr();
    }

    const auto &puzzles = puzzleResult.getOk();
    for (int i = 0; i < 7; i++) {
        newPuzzle = puzzles.at(i);
        std::cout << "Puzzle-ul pe care trebuie sa-l rezolvi este: \n" << *newPuzzle << std::endl;

        if (std::dynamic_pointer_cast<buttonsInOrder>(newPuzzle)) {
            std::cout << "Pentru a rezolva puzzle-ul trebuie sa apasati butoanele in ordinea crescatoare a numerelor care apar.\n" << std::endl;
        } else if (std::dynamic_pointer_cast<tagZones>(newPuzzle)) {
            std::cout << "Pentru a rezolva puzzle-ul trebuie sa formati zone din blocuri adiacente. 2 blocuri sunt adiacente daca sunt una langa alta(inclusiv pe diagonala)\n" << std::endl;
        }

        newPuzzle->setAnswer(newPuzzle->getAnswer());

        if (newPuzzle->checkAnswer() == 1) {
            std::cout << "You have solved this puzzle. You have been awarded " << newPuzzle->getPoints() << " points." << std::endl;
            player.setPoints(player.getPoints() + newPuzzle->getPoints());
        } else {
            std::cout << "You have failed to solve the puzzle.";
        }
    }
}
