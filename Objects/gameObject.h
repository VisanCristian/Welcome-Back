//
// Created by visan on 11/1/25.
//

#ifndef OOP_GAMEOBJECT_H
#define OOP_GAMEOBJECT_H

#include <string>
#include "Puzzle.h"
#include "Player.h"


class gameObject {
    std::string name;
    int puzzleNr;
    int solvedPuzzles;
    int difficulty;

    Player player;

    void checkPoint();
    void genPuzzle(Puzzle& puzzle);

    static void inputThread(Puzzle &puzzle, std::vector<int> &answer);
    static void timerThread(Puzzle &puzzle);

    static std::string generateFinalKey(const std::vector<std::string> &keys);

public:

    gameObject(const std::string& name, int difficulty, const Player &player);
    gameObject(const gameObject& other);
    gameObject& operator=(const gameObject& other);
    ~gameObject();

    friend std::ostream& operator<<(std::ostream& os, const gameObject& obj);

    void start();
    static void gameOver(const std::string &reason);
    static void winGame(const std::string& finalKey);
    [[nodiscard]] int getDifficulty() const { return difficulty;};

};


#endif //OOP_GAMEOBJECT_H