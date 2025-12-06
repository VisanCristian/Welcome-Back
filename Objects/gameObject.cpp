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
    std::string key = computer.getKey();
    player.setPoints(player.getPoints() - keyPrice);
    player.addKey(key);
    setKeyPrice();
    std::cout << "You have succesfully completed this milestone and bought key #" << milestone << " : " << key << std::endl;
    milestone++;
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
        {1, 5},
        {2, 10},
        {3, 15},
        {4, 20},
        {5, 25},
        {6, 30}
    };
    keyPrice = keyPrices[milestone];
}


void gameObject::start() {
    while (true) {
        computer.eventLoop(milestone, player);
        std::cout << "The milestone is over and the player has " << player.getPoints() << " points." << std::endl;
        checkPoint();
        if(milestone ==7) {
            player.setFinalKey(generateFinalKey(player.getKeys()));
            winGame(player.getFinalKey());
            exit(0);
        }
    }
}

std::chrono::steady_clock::time_point gameObject::getTime() const {
    std::chrono::steady_clock::time_point now;
    return std::chrono::steady_clock::time_point(now - this->startTime);
}



