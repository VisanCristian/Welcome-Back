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
    int pointsTotal;
    std::string finalKey;
public:
    Player();
    Player(const Player& other);
    ~Player();


    Player& operator=(const Player& other);

    [[nodiscard]] const std::vector<std::string>& getKeys() const { return keys; }
    const std::string& getFinalKey() const;
    void setFinalKey(const std::string &key);
    void addKey(const std::string& key);

    int getPoints() const;
    void setPoints(const int points);


    friend std::ostream& operator<<(std::ostream& os,  const Player& player);

};


#endif //OOP_PLAYER_H
