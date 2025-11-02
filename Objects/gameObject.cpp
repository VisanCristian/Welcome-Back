//
// Created by visan on 11/1/25.
//

#include "gameObject.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "Puzzle.h"


// Modify TTY blocking mode

void setBlockingMode(bool enable) {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    if (enable) {
        ttystate.c_lflag &= ~ICANON; // Disable canonical mode
        ttystate.c_lflag &= ~ECHO;   // Disable echo
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    } else {
        ttystate.c_lflag |= ICANON;
        ttystate.c_lflag |= ECHO;
        fcntl(STDIN_FILENO, F_SETFL, 0);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}


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


void gameObject::inputThread(Puzzle &puzzle, std::vector<int> &answer) {
    answer = Puzzle::getAnswer();
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

void gameObject::genPuzzle(const std::string& puzzleType) {

    // Set tty to non-blocking mode

    // Generates a Puzzle
    Puzzle newPuzzle(puzzleType);
    newPuzzle.setSolved(false);
    newPuzzle.setTimeUp(false);

    std::cout << newPuzzle;
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
    }
}




void gameObject::checkPoint() {
    // Checks the current state of the game
    std::cout << "CheckPoint" << std::endl;

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
    while (solvedPuzzles < puzzleNr) {
        checkPoint();
        genPuzzle("buttonsInOrder");
    }
}



