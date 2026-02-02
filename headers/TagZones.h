#ifndef OOP_TAGZONES_H
#define OOP_TAGZONES_H

#include "headers/Puzzle.h"

class TagZones : public Puzzle{
protected:
    int timeLimit;
    void generatePuzzle() override;
    void setCorrectAnswer();
    void print(std::ostream& os) const override;
public:
    TagZones(int timeLimit, int points, int size) : timeLimit(timeLimit) {
        this->points = points;
        userAnswer.resize(size);
        TagZones::generatePuzzle();
        setCorrectAnswer();
    };
    ~TagZones() override = default;

    friend std::ostream& operator<<(std::ostream& os, const TagZones& obj);

    [[nodiscard]] std::unique_ptr<Puzzle> clone() const override;

    std::vector<int> getUserInput() override;
    void setAnswer(const std::vector<int>& answer) override;
    int getTimeLimit() const override { return this->timeLimit; };
    [[nodiscard]] bool checkAnswer() const override;
};

#endif
