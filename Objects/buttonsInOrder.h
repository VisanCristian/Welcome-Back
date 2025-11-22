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

public:
    explicit buttonsInOrder(const int timeLimit) : timeLimit(timeLimit) {
        points = 5;
        buttonsInOrder::generatePuzzle();
        generateKey();
        setCorrectAnswer();
        userAnswer.resize(10);
    };
    ~buttonsInOrder() override = default;

    friend std::ostream& operator<<(std::ostream& os, const buttonsInOrder& obj);

    std::vector<int> getAnswer() override;
    std::vector<int> getUserInput() override;
    void setAnswer(const std::vector<int>& Answer) override;
    int getTimeLimit() const override{return this->timeLimit;};

    [[nodiscard]] bool checkAnswer() const override;

};


#endif //OOP_BUTTONSINORDER_H