//
// Created by visan on 12/7/25.
//

#ifndef OOP_PATHFINDING_H
#define OOP_PATHFINDING_H

#include "Puzzle.h"

class PathFinding : public Puzzle {
protected:
    int timeLimit;

    void generatePuzzle() override;
    void setCorrectAnswer();
    void print(std::ostream& os) const override;

public:
    PathFinding(int timeLimit, int points, int size);
    ~PathFinding() override = default;

    friend std::ostream& operator<<(std::ostream& os, const PathFinding& obj);

    [[nodiscard]] std::unique_ptr<Puzzle> clone() const override;

    [[nodiscard]] std::vector<int> getAnswer() override;
    std::vector<int> getUserInput() override;
    void setAnswer(const std::vector<int>& Answer) override;
    int getTimeLimit() const override { return this->timeLimit; };
    [[nodiscard]] bool checkAnswer() const override;
};


#endif //OOP_PATHFINDING_H
