//
// Created by visan on 11/1/25.
//

#include "gameObject.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Puzzle.h"


// Constructor

gameObject::gameObject(const std::string& name, const int difficulty, const Player &player) : name(name),difficulty(difficulty), player(player) {
    std::cout << "Game Started! In order to find out the truth about your brother you have to find all the keys by solving the puzzles. Click each number in the right order!" << std::endl;
    this->solvedPuzzles = 0;
    // Constructor implementation
    if (difficulty == 1) {
        puzzleNr = 1;
    } else if (difficulty == 2) {
        puzzleNr = 2;
    } else {
        puzzleNr = 3;
    }
}

// Destructor
gameObject::~gameObject() = default;


std::ostream& operator<<(std::ostream& os, const gameObject& obj) {
    os << "Game Object: " << obj.name << "\n";
    os << "Difficulty Level: " << obj.difficulty << "\n";
    os << "Total Puzzles: " << obj.puzzleNr << "\n";
    os << "Solved Puzzles: " << obj.solvedPuzzles << "\n";
    return os;
}

void gameObject::timerThread(const Puzzle& puzzle) {
    std::cout << "You have " << puzzle.getTimeLimit() << " seconds to solve the puzzle!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(puzzle.getTimeLimit()));
    if (puzzle.getSolved() == false) {
        if (player.getAttemptsLeft() > 0) {
            player.setAttemptsLeft(player.getAttemptsLeft() - 1);
            std::cout << "Time is up! You have " << player.getAttemptsLeft() << " attempts left. Try not to get any more puzzles wrong" << std::endl;
            exit(0);
        } else {
            std::string reason = "Time limit exceeded for puzzle";
            gameOver(reason);
            exit(0);
        }
    }
}

void gameObject::genPuzzle(const std::string& puzzleType) {
    // Generates a Puzzle
    Puzzle newPuzzle(puzzleType);
    std::cout << newPuzzle;

    newPuzzle.setTimeUp(false);
    std::thread timer(&gameObject::timerThread, this, std::ref(newPuzzle));
    timer.detach();

    const std::vector<int> answer = Puzzle::getAnswer();
    newPuzzle.setAnswer(answer);

    if (newPuzzle.getTimeUp() == true) {
        gameOver("Time is up");
        exit(0);
    }

    if (newPuzzle.checkAnswer() == 0 && player.getAttemptsLeft() == 0) {
        gameOver("Your answer is incorrect");
        exit(0);
    } else if (newPuzzle.checkAnswer() == 0 && player.getAttemptsLeft() > 0) {
        player.setAttemptsLeft(player.getAttemptsLeft() - 1);
        std::cout << "Incorrect answer! You have " << player.getAttemptsLeft() << " attempts left. Try not to get any more puzzles wrong" << std::endl;
    }else {
        solvedPuzzles++;
        newPuzzle.setSolved(true);
        std::cout << "Correct answer! You have solved " << solvedPuzzles << " puzzles." << std::endl;
    }
}

void gameObject::checkPoint() const {
    // Checks the current state of the game
    std::cout << "CheckPoint" << std::endl;

    if (solvedPuzzles == puzzleNr) {
        std::cout << "Congratulations! You have solved all puzzles! The game is over" << std::endl;
        exit(0);
    }

    std::cout << "You are currently on puzzle: " << solvedPuzzles + 1 << " out of " << puzzleNr << std::endl;

}

void gameObject::gameOver(const std::string &reason) {
    std::cout << "Game Over! Reason: " << reason << std::endl;
    exit(0);
}

void gameObject::winGame(const std::string& finalKey) {
    std::cout << "Use this code to decrypt the files your brother left you... TO BE CONTINUED..." << std::endl;
    std::cout << "Final Key: " << finalKey << std::endl;
    exit(0);
}


void gameObject::start() {
    for (int i = 0; i < puzzleNr; i++) {
        checkPoint();
        genPuzzle("buttonsInOrder");
    }
}



