//
// Created by visan on 11/1/25.
//

#include "gameObject.h"
#include "GameErrors.h"
#include <iostream>



// Constructor

gameObject::gameObject(const std::string& name, const Player &player, const Computer& Computer) : name(name), player(player), computer(Computer){
    std::cout << "Game Started! In order to find out the truth about your brother you have to find all the keys by solving the puzzles. \n" << std::endl;
    this->milestone = 1;
    this->puzzleNr = 1;
    setKeyPrice();
}

gameObject::gameObject(const gameObject &other)
    : name(other.name),
      startTime(other.startTime),
      keyPrice(other.keyPrice),
      puzzleNr(other.puzzleNr),
      milestone(other.milestone),
      player(other.player),
      computer(other.computer) {}

gameObject & gameObject::operator=(const gameObject &other) {
    if (this != &other) {
        name = other.name;
        startTime = other.startTime;
        keyPrice = other.keyPrice;
        puzzleNr = other.puzzleNr;
        milestone = other.milestone;
        player = other.player;
        computer = other.computer;
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

    Result<std::string, GameError> keyResult = computer.getKey();
    if (!keyResult.isOk()) {
        gameOver(keyResult.getErr().what());
        return;
    }

    const std::string &key = keyResult.getOk();
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
        {1, 700},
        {2, 800},
        {3, 900},
        {4, 1000},
        {5, 1100},
        {6, 1200}
    };

    auto it = keyPrices.find(milestone);
    if (it == keyPrices.end()) {
        throw GameError("gameObject::setKeyPrice - invalid milestone " + std::to_string(milestone));
    }
    keyPrice = it->second;
}


void gameObject::start() {
    try {
        while (true) {
            computer.eventLoop(milestone, player);
            std::cout << "The milestone is over and the player has " << player.getPoints() << " points." << std::endl;
            checkPoint();
            if (milestone == 7) {
                player.setFinalKey(generateFinalKey(player.getKeys()));
                winGame(player.getFinalKey());
                exit(0);
            }
        }
    } catch (const ConstructorError &e) {
        gameOver(e.what());
    } catch (const GameError &e) {
        gameOver(e.what());
    } catch (const InternalError &e) {
        gameOver(e.what());
    } catch (const std::exception &e) {
        gameOver(e.what());
    }
}

