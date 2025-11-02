//
// Created by visan on 11/1/25.
//

#include "gameObject.h"
#include "Puzzle.h"
#include "buttonsInOrder.h"
#include "tagZones.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>


// Modify TTY blocking mode

// Constructor

gameObject::gameObject(const std::string& name, const int difficulty, const Player &player) : name(name),difficulty(difficulty), player(player) {
    std::cout << "Game Started! In order to find out the truth about your brother you have to find all the keys by solving the puzzles. \n" << std::endl;
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

gameObject::gameObject(const gameObject &other) : name(other.name), puzzleNr(other.puzzleNr), solvedPuzzles(other.solvedPuzzles), difficulty(other.difficulty), player(other.player) {}

gameObject & gameObject::operator=(const gameObject &other) {
    if (this != &other) {
        name = other.name;
        puzzleNr = other.puzzleNr;
        solvedPuzzles = other.solvedPuzzles;
        difficulty = other.difficulty;
        player = other.player;
    }
    return *this;
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


void gameObject::inputThread(Puzzle &puzzle, std::vector<int> &answer) {
    answer = puzzle.getAnswer();
    puzzle.setAnswer(answer);
    puzzle.setSolved(true);
}

void gameObject::timerThread(Puzzle &puzzle) {
    for (int i = 0; i < 10 * puzzle.getTimeLimit(); i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (puzzle.getSolved() == true) return;
    }
    if (puzzle.getSolved() == false) {
        puzzle.setTimeUp(true);
    }
}

void gameObject::genPuzzle(Puzzle& newPuzzle) {

    newPuzzle.setSolved(false);
    newPuzzle.setTimeUp(false);

    std::vector<int> userAnswer;

    std::thread input(inputThread, std::ref(newPuzzle), std::ref(userAnswer));
    std::thread timer(timerThread, std::ref(newPuzzle));


    while (true) {
        if (newPuzzle.getSolved() == true) {break;}
        if (newPuzzle.getTimeUp() == true) {
            gameOver("Time is up!");

            std::exit(0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    std::cout << newPuzzle;

    input.join();
    timer.join();

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
        player.addKey(newPuzzle.getKey());
    }
}




void gameObject::checkPoint() {
    // Checks the current state of the game
    std::cout << "CheckPoint" << std::endl;
    std::cout << player;
    if (solvedPuzzles == puzzleNr) {
        player.setFinalKey(generateFinalKey(player.getKeys()));
        winGame(player.getFinalKey());
        exit(0);
    }

    std::cout << "You are currently on puzzle: " << solvedPuzzles + 1 << " out of " << puzzleNr << std::endl;

}

std::string gameObject::generateFinalKey(const std::vector<std::string> &keys) {
    std::string finalKey;
    for (const auto& key : keys) {
        finalKey += "%" + key;
    }
    return finalKey;
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
    while (solvedPuzzles <= puzzleNr) {
        checkPoint();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 100);
        if (dist(gen) % 2 == 0) {
            buttonsInOrder tmp(10);
            genPuzzle(tmp);
        } else {
            tagZones tmp(10);
            genPuzzle(tmp);
        }

    }
}



