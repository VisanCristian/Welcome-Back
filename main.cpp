#include <iostream>
#include <fstream>

#include "Objects/gameObject.h"
#include "Objects/Player.h"
#include "Objects/Puzzle.h"

std::ifstream fin("tastatura.txt");

using namespace std;

int main() {
    int difficulty, attempts;
    fin >> difficulty >> attempts;

    Player player(attempts);
    gameObject game("game1", difficulty, player);

    for (int i = 0; i < game.getDifficulty(); i++) {
        Puzzle puzzle("buttonsInOrder");
        cout << "Puzzle "<< i << ":\n" <<puzzle << endl;
        vector<int> userAnswer = puzzle.getAnswer();
        puzzle.setAnswer(userAnswer);
        if (puzzle.checkAnswer()) {
            cout << "Puzzle solved!" << endl;
            player.addKey(puzzle.getKey());
        } else if (player.getAttemptsLeft() == 0) {
            game.gameOver("Wrong answer. No attempts left.");
            return 0;
        } else {
            player.setAttemptsLeft(player.getAttemptsLeft() - 1);
            cout << "Wrong answer. Attempts left: " << player.getAttemptsLeft() << endl;
        }
        cout << player << endl;
    }
    std::string finalKey;
    for (unsigned long int i = 0; i < player.getKeys().size(); i++) {
        finalKey += player.getKeys()[i];
    }
    cout << finalKey << endl;
    game.winGame(finalKey);

    game.start();
    return 0;
}
