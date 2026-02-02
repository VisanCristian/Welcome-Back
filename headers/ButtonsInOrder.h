#ifndef OOP_BUTTONSINORDER_H
#define OOP_BUTTONSINORDER_H

#include "headers/Puzzle.h"

class ButtonsInOrder : public Puzzle {
    int timeLimit;

    void generatePuzzle() override;
    void setCorrectAnswer();
    void print(std::ostream& os) const override;

public:
    ButtonsInOrder(int timeLimit, int points, int size) : timeLimit(timeLimit) {
        this->points = points;
        userAnswer.resize(size);
        ButtonsInOrder::generatePuzzle();
        setCorrectAnswer();
    };
    ~ButtonsInOrder() override = default;

    friend std::ostream& operator<<(std::ostream& os, const ButtonsInOrder& obj);

    [[nodiscard]] std::unique_ptr<Puzzle> clone() const override;

    std::vector<int> getUserInput() override;
    void setAnswer(const std::vector<int>& answer) override;
    int getTimeLimit() const override { return this->timeLimit; };

    [[nodiscard]] bool checkAnswer() const override;
};

#endif
