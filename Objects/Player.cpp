//
// Created by visan on 11/1/25.
//

#include "Player.h"

Player::Player(const Player &other) {
    this->keys = other.keys;
    this->pointsTotal = other.pointsTotal;
    this->finalKey = other.finalKey;
}

Player & Player::operator=(const Player &other) {
    if (this != &other) {
        this->keys = other.keys;
        this->pointsTotal = other.pointsTotal;
        this->finalKey = other.finalKey;
    }
    return *this;
}


Player::Player() = default;
Player::~Player() = default;

void Player::addKey(const std::string& key) {
    keys.push_back(key);
}

int Player::getPoints() const {
    return pointsTotal;
}

const std::string& Player::getFinalKey() const{
    return finalKey;
}

void Player::setFinalKey(const std::string& key) {
    finalKey = key;
}


std::ostream& operator<<(std::ostream& os,  const Player& player) {
    os << "Player keys: \n";
    if (player.keys.empty()) {
        os << "No keys collected.\n";
        return os;
    }
    for (unsigned long i = 0; i < player.keys.size(); i++) {
        os << "Player key " << i + 1 << ":";
        os << " " << player.keys[i] << "\n";
    }
    return os;
}