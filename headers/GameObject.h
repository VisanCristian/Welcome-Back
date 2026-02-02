#ifndef OOP_GAMEOBJECT_H
#define OOP_GAMEOBJECT_H

#include <string>
#include <chrono>
#include <vector>

#include "headers/Computer.h"
#include "headers/Player.h"

template<typename T>
std::string join(const std::vector<T>& elements, const std::string& delimiter) {
    std::string result;
    for (const auto& elem : elements) {
        result += delimiter;
        result += elem;
    }
    return result;
}

class GameObject {
    std::string name;
    std::chrono::steady_clock::time_point startTime;
    int keyPrice;
    int puzzleNr;
    int milestone;
    Player player;
    Computer computer;

    void checkPoint();

    static void gameOver(const std::string &reason);
    static void winGame(const std::string& finalKey);
    void setKeyPrice();
    std::string generateKey();

    GameObject();

public:
    GameObject(const GameObject& other) = delete;
    void operator=(const GameObject& other) = delete;
    ~GameObject();

    static GameObject& getInstance();
    void init(const std::string& name, const Player& player, const Computer& computer);

    friend std::ostream& operator<<(std::ostream& os, const GameObject& obj);

    void start();
};

#endif
