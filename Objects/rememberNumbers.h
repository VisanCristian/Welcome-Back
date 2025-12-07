#ifndef OOP_REMEMBERNUMBERS_H
#define OOP_REMEMBERNUMBERS_H

#include "Puzzle.h"
#include "GameErrors.h"

class rememberNumbers : public Puzzle {
protected:
    int timeLimit;
    void generatePuzzle() override;
    void setCorrectAnswer();
    void print(std::ostream& os) const override;
public:

    rememberNumbers(const int timelimit, const int points, const int size); 
    ~rememberNumbers() override = default;

    friend std::ostream& operator<<(std::ostream& os, const rememberNumbers& obj);

    [[nodiscard]] std::unique_ptr<Puzzle> clone() const override;

    
    int getTimeLimit() const override;
    std::vector<int> getUserInput() override;
    void setAnswer(const std::vector<int>& Answer) override;
    [[nodiscard]] bool checkAnswer() const override;
};


#endif //OOP_REMEMBERNUMBERS_H
