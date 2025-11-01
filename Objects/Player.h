//
// Created by visan on 11/1/25.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H


#include <iostream>
#include <vector>
#include <string>

class Player {
    std::vector<std::string> keys;
    int attemptsLeft;
    std::string finalKey;
public:
    Player() {this->attemptsLeft = 0;};
    explicit Player(int attemptsLeft);
    ~Player();

    void addKey(const std::string& key);
    std::vector<std::string>& getKeys() {return keys;}

    const std::string& getFinalKey() const;
    void setFinalKey(const std::string &key);

    int getAttemptsLeft() const;
    void setAttemptsLeft(const int attempts);



    friend std::ostream& operator<<(std::ostream& os,  const Player& player);

};


#endif //OOP_PLAYER_H