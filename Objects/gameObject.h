//
// Created by visan on 11/1/25.
//

#ifndef OOP_GAMEOBJECT_H
#define OOP_GAMEOBJECT_H

#include <string>

#include "Computer.h"
#include "Puzzle.h"
#include "Player.h"


class gameObject {
    std::string name;
    std::chrono::steady_clock::time_point startTime;
    int keyPrice;
    int puzzleNr;
    int milestone;
    Player player;
    Computer computer;

    void checkPoint();
    void genPuzzle(Puzzle& puzzle);

    static void inputThread(Puzzle &puzzle, std::vector<int> &answer);
    static void timerThread(Puzzle &puzzle);

    static std::string generateFinalKey(const std::vector<std::string> &keys);
    static void gameOver(const std::string &reason);
    static void winGame(const std::string& finalKey);
    void setKeyPrice();
    std::string generateKey();
public:

    gameObject(const std::string& name, const Player &player, const Computer& Computer);
    gameObject(const gameObject& other);
    ~gameObject();

    gameObject& operator=(const gameObject& other);
    friend std::ostream& operator<<(std::ostream& os, const gameObject& obj);

    void start();

    [[nodiscard]] int getDifficulty() const { return milestone;};
    [[nodiscard]] std::chrono::steady_clock::time_point getTime() const;

};


#endif //OOP_GAMEOBJECT_H