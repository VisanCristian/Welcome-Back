//
// Created by visan on 11/1/25.
//

#include "gameObject.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>



// Constructor

gameObject::gameObject(const std::string& name, const Player &player, const Computer& Computer) : name(name), player(player), computer(Computer){
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
void gameObject::checkPoint() {
    if (player.getPoints() < keyPrice) {
        gameOver("You don't have enough points to buy a key!");
        exit(1);
    }
    computer.buyKey(player);
    setKeyPrice();
    std::cout << "You have succesfully completed this milestone and bought key#" << milestone << std::endl;
    milestone++;
}

std::string gameObject::generateKey() {
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
    computer.eventLoop(milestone);
}

std::chrono::steady_clock::time_point gameObject::getTime() const {
    std::chrono::steady_clock::time_point now;
    return std::chrono::steady_clock::time_point(now - this->startTime);
}



