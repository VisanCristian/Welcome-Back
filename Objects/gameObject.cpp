//
// Created by visan on 11/1/25.
//

#include "gameObject.h"

#include <algorithm>

#include "Puzzle.h"
#include "buttonsInOrder.h"
#include "tagZones.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>



// Constructor

gameObject::gameObject(const std::string& name, const Player &player, const Computer& Computer) : name(name), player(player), computer(computer){
    std::cout << "Game Started! In order to find out the truth about your brother you have to find all the keys by solving the puzzles. \n" << std::endl;
    this->milestone = 1;
    this->puzzleNr = 1;
    setKeyPrice();
}

gameObject::gameObject(const gameObject &other) : name(other.name), puzzleNr(other.puzzleNr), player(other.player), computer(other.computer), milestone(other.milestone), keyPrice(other.keyPrice) {}

gameObject & gameObject::operator=(const gameObject &other) {
    if (this != &other) {
        name = other.name;
        puzzleNr = other.puzzleNr;
        computer = other.computer;
        milestone = other.milestone;
        player = other.player;
    }
    return *this;
}



// Destructor
gameObject::~gameObject() = default;


std::ostream& operator<<(std::ostream& os, const gameObject& obj) {
    os << "Game Object: " << obj.name << "\n";
    os << "Currently on milestone: " << obj.milestone << "\n";
    os << "Currently you have to solve the puzzle nr : " << obj.puzzleNr << "\n";
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
        newPuzzle.setSolved(true);
        std::cout << "You have solved the puzzle. You have been awarded" << newPuzzle.getPoints() << " points." << std::endl;
        player.addKey(newPuzzle.getKey());
    }
}




void gameObject::checkPoint() {
    if (player.getPoints() < keyPrice) {
        gameOver("You don't have enough points to buy a key!");
        exit(1);
    }
    computer.buyKey(player);
    setKeyPrice();
    std::cout << "You have succesfully completed this milestone and bought key#" << milestone << std::end;
    milestone++;
}

std::string generateKey() {
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
    std::ranges::shuffle(key, gen);
    return key;
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

void gameObject::setKeyPrice() {
    std::unordered_map<int, int> keyPrices {
        {1, 100},
        {2, 200},
        {3, 450},
        {4, 750},
        {5, 1000},
        {6, 1500}
    };
    keyPrice = keyPrices[milestone];
}


void gameObject::start() {
    computer.genPuzzle();
}

std::chrono::steady_clock::time_point gameObject::getTime() const {
    std::chrono::steady_clock::time_point now;
    return std::chrono::steady_clock::time_point(now - this->startTime);
}



