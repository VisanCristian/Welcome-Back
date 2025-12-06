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
protected:

    int points = 0; // number of points awarded for solving this puzzle
    std::vector<int> puzzle;
    std::vector<int> userAnswer;
    std::vector<int> correctAnswer;

    //std::string puzzleType;
    std::atomic<bool> solved;
    std::atomic<bool> timeUp;
    virtual void generatePuzzle() = 0;
	
    
public:
    Puzzle();
    virtual ~Puzzle() = default;

    friend std::ostream& operator<<(std::ostream& os, const Puzzle& obj);

    virtual std::vector<int> getAnswer() = 0;
    virtual std::vector<int> getUserInput() = 0;
    virtual void setAnswer(const std::vector<int>& Answer) = 0;
    virtual int getTimeLimit() const = 0;
    virtual bool checkAnswer() const = 0;

    [[nodiscard]] virtual int getPoints() const; // allow Computer to query puzzle points

    void setSolved(bool status);
    bool getSolved() const;
    void setTimeUp(const bool status);
    bool getTimeUp() const;




};


#endif //OOP_PUZZLE_H