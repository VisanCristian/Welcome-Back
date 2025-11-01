//
// Created by visan on 11/1/25.
//

#include "Player.h"

Player::Player(int attemptLeft) : attemptsLeft(attemptLeft) {};
Player::~Player() = default;

void Player::addKey(const std::string& key) {
    keys.push_back(key);
}

std::string Player::getFinalKey() const {
    return finalKey;
}

void Player::setFinalKey(const std::string& key) {
    finalKey = key;
}

int Player::getAttemptsLeft() const {
    return attemptsLeft;
}

void Player::setAttemptsLeft(const int attempts) {
    attemptsLeft = attempts;
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