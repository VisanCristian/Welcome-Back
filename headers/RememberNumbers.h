#ifndef OOP_REMEMBERNUMBERS_H
#define OOP_REMEMBERNUMBERS_H

#include "headers/Puzzle.h"

class RememberNumbers : public Puzzle {
protected:
    int timeLimit;
    void generatePuzzle() override;
    void setCorrectAnswer();
    void print(std::ostream& os) const override;
public:
    RememberNumbers(int timeLimit, int points, int size);
    ~RememberNumbers() override = default;

    friend std::ostream& operator<<(std::ostream& os, const RememberNumbers& obj);

    [[nodiscard]] std::unique_ptr<Puzzle> clone() const override;

    int getTimeLimit() const override;
    std::vector<int> getUserInput() override;
    void setAnswer(const std::vector<int>& answer) override;
    [[nodiscard]] bool checkAnswer() const override;
};

#endif
