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
    void setCorrectAnswer(const std::vector<int> &puzzle);
public:

    explicit tagZones(const int timeLimit) : timeLimit(timeLimit) {generatePuzzle(); generateKey(); setCorrectAnswer(puzzle); userAnswer.resize(9);};
    ~tagZones() override = default;

    friend std::ostream& operator<<(std::ostream& os, const tagZones& obj);

    std::vector<int> getAnswer() override;
    void setAnswer(const std::vector<int>& Answer) override;
    int getTimeLimit() const override{return this->timeLimit;};
    [[nodiscard]] bool checkAnswer() const override;
};


#endif //OOP_TAGZONES_H