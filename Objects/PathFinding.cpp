//
// Created by visan on 12/7/25.
//

#include "PathFinding.h"
#include "GameErrors.h"

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <queue>
#include <map>


PathFinding::PathFinding(int timeLimit, int points, int size) : timeLimit(timeLimit){
    this->points = points;
    userAnswer.resize(size);

    PathFinding::generatePuzzle();
    setCorrectAnswer();
}

void PathFinding::generatePuzzle() {
    const int side = static_cast<int>(userAnswer.size());
    if (side <= 0) {
        throw ConstructorError("PathFinding::generatePuzzle - invalid puzzle side length");
    }

    // Directory pattern: assets/PathFinder/sidexside/
    std::string dirPath = "assets/PathFinder/" + std::to_string(side) + "x" + std::to_string(side) + "/";

    // Pick a random puzzle file index in [1, 5]
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5);
    int fileIndex = dist(gen);

    std::string filePath = dirPath + std::to_string(fileIndex);
    std::ifstream fin(filePath);
    if (!fin) {
        throw ConstructorError("PathFinding::generatePuzzle - could not open puzzle file: " + filePath);
    }

    puzzle.clear();
    puzzle.reserve(static_cast<size_t>(side) * static_cast<size_t>(side));

    int value = 0;
    while (fin >> value) {
        puzzle.push_back(value);
    }

    // Expect exactly side*side entries; otherwise the file is malformed.
    if (static_cast<int>(puzzle.size()) != side * side) {
        throw InvalidConfigFile(filePath);
    }
}

void PathFinding::setCorrectAnswer() {
    correctAnswer = userAnswer;
}

std::vector<int> PathFinding::getUserInput() {
    int startRow = 0;
    int startCol = 0;
    int height = static_cast<int>(userAnswer.size());
    int width = static_cast<int>(userAnswer.size());
    int endRow = height - 1;
    int endCol = width - 1;

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    std::queue<int> q;
    int startIndex = startRow * width + startCol;
    q.push(startIndex);

    std::map<int, int> parents;
    parents[startIndex] = -1;

    std::vector<bool> visited(width * height, false);
    visited[startIndex] = true;

    bool found = false;
    int endIndex = endRow * width + endCol;

    while (!q.empty()) {
        int currentIdx = q.front();
        q.pop();

        int r = currentIdx / width;
        int c = currentIdx % width;

        if (currentIdx == endIndex) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < height && nc >= 0 && nc < width) {
                int nIdx = nr * width + nc;
                if (this->puzzle[nr * width + nc] != -1 && !visited[nIdx]) {
                    visited[nIdx] = true;
                    parents[nIdx] = currentIdx;
                    q.push(nIdx);
                }
            }
        }
    }

    std::vector<int> solutionPath;

    if (found) {
        int curr = endIndex;
        while (curr != -1) {
            solutionPath.push_back(curr);
            curr = parents[curr];
        }
        std::reverse(solutionPath.begin(), solutionPath.end());
    }
    correctAnswer = solutionPath;
    return solutionPath;
}

void PathFinding::print(std::ostream& os) const {
    os << "Puzzle: \n";
    for (int i = 0; i < static_cast<int>(puzzle.size()); i++) {
        os << puzzle[i] << " ";
    }
    os << std::endl;
}


std::vector<int> PathFinding::getAnswer(){
    getUserInput();
    return correctAnswer;
}

void PathFinding::setAnswer(const std::vector<int>& Answer) {
    this->userAnswer = Answer;
}

bool PathFinding::checkAnswer() const {
    return userAnswer == correctAnswer;
}

std::unique_ptr<Puzzle> PathFinding::clone() const {
    return std::make_unique<PathFinding>(*this);
}

