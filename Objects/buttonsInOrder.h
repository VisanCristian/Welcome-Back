//
// Created by visan on 11/2/25.
//

#ifndef OOP_BUTTONSINORDER_H
#define OOP_BUTTONSINORDER_H

#include "Puzzle.h"

class buttonsInOrder : public Puzzle {
    int timeLimit;

    void generatePuzzle() override;
    void setCorrectAnswer();
    void print(std::ostream& os) const override;

public:
    buttonsInOrder(const int timeLimit, const int points, const int size) : timeLimit(timeLimit) {
        this->points = points;
        userAnswer.resize(size);
        buttonsInOrder::generatePuzzle();
        setCorrectAnswer();
    };
    ~buttonsInOrder() override = default;

    friend std::ostream& operator<<(std::ostream& os, const buttonsInOrder& obj);

    [[nodiscard]] std::unique_ptr<Puzzle> clone() const override;

    [[nodiscard]] std::vector<int> getAnswer() override;
    std::vector<int> getUserInput() override;
    void setAnswer(const std::vector<int>& Answer) override;
    int getTimeLimit() const override { return this->timeLimit; };

    [[nodiscard]] bool checkAnswer() const override;

};


#endif //OOP_BUTTONSINORDER_H
