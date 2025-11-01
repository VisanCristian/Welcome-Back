//
// Created by visan on 11/1/25.
//

#ifndef OOP_PUZZLE_H
#define OOP_PUZZLE_H

#include <iosfwd>
#include <vector>
#include <string>
#include <unordered_map>
#include <atomic>

class Puzzle {

    std::unordered_map<std::string, int> puzzleTimeLimits {
       {"buttonsInOrder", 10},
    };

    std::vector<int> puzzle;
    std::vector<int> userAnswer;
    std::vector<int> correctAnswer;
    std::string puzzleType;
    std::string key;
    std::atomic<bool> solved;
    std::atomic<bool> timeUp;
    void generatePuzzle();
    void generateKey();

public:
    explicit Puzzle(const std::string& type);
    Puzzle(const Puzzle& other);

    friend std::ostream& operator<<(std::ostream& os, const Puzzle& obj);
    Puzzle& operator=(const Puzzle& other);


    static std::vector<int> getAnswer();
    void setAnswer(const std::vector<int>& Answer);
    int getTimeLimit() const;
    void setSolved(bool status);
    bool getSolved() const;
    void setTimeUp(const bool status);
    bool getTimeUp() const;
    std::string getKey() const { return key; }

   [[nodiscard]] bool checkAnswer() const;



};


#endif //OOP_PUZZLE_H