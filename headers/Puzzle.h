#ifndef OOP_PUZZLE_H
#define OOP_PUZZLE_H

#include <iosfwd>
#include <vector>
#include <string>
#include <unordered_map>
#include <atomic>
#include <memory>

class Puzzle {
protected:
    int points = 0;
    std::vector<int> puzzle;
    std::vector<int> userAnswer;
    std::vector<int> correctAnswer;

    std::atomic<bool> solved;
    std::atomic<bool> timeUp;

    virtual void generatePuzzle() = 0;
    virtual void print(std::ostream& os) const = 0;

public:
    Puzzle();
    Puzzle(const Puzzle& other);
    Puzzle& operator=(const Puzzle& other);
    virtual ~Puzzle() = default;

    friend std::ostream& operator<<(std::ostream& os, const Puzzle& obj);

    [[nodiscard]] virtual std::unique_ptr<Puzzle> clone() const = 0;

    virtual std::vector<int> getUserInput() = 0;
    virtual void setAnswer(const std::vector<int>& answer) = 0;
    virtual int getTimeLimit() const = 0;
    virtual bool checkAnswer() const = 0;

    [[nodiscard]] virtual int getPoints() const;

    void setTimeUp(bool status);
};

#endif
