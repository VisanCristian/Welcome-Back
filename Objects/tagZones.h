//
// Created by visan on 11/2/25.
//

#ifndef OOP_TAGZONES_H
#define OOP_TAGZONES_H

#include "Puzzle.h"

class tagZones : public Puzzle{
protected:
    int timeLimit;
    void generatePuzzle() override;
    void setCorrectAnswer();
    void print(std::ostream& os) const override;
public:

    tagZones(const int timeLimit, const int points, const int size) : timeLimit(timeLimit) {
        this->points = points;
        userAnswer.resize(size);
        tagZones::generatePuzzle();
        setCorrectAnswer();
    };
    ~tagZones() override = default;

    friend std::ostream& operator<<(std::ostream& os, const tagZones& obj);

    [[nodiscard]] std::unique_ptr<Puzzle> clone() const override;

    [[nodiscard]] std::vector<int> getAnswer() const override;
    std::vector<int> getUserInput() override;
    void setAnswer(const std::vector<int>& Answer) override;
    int getTimeLimit() const override { return this->timeLimit; };
    [[nodiscard]] bool checkAnswer() const override;
};


#endif //OOP_TAGZONES_H
