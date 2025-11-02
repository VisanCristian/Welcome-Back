#include <fstream>

#include "Objects/gameObject.h"
#include "Objects/Player.h"
#include "Objects/Puzzle.h"

std::ifstream fin("tastatura.txt");

using namespace std;

int main() {
   int difficulty, attempts;
    fin >> difficulty >> attempts;
    cout << difficulty << attempts << endl;
    Player player(attempts);
    gameObject game("game1", difficulty, player);

    for (int i = 0; i < game.getDifficulty(); i++) {
        Puzzle puzzle("buttonsInOrder");
        vector<int> userAnswer = puzzle.getAnswer();
        puzzle.setAnswer(userAnswer);
        cout << "Puzzle "<< i << ":\n" <<puzzle << endl;
        if (puzzle.checkAnswer() == true) {
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
        finalKey += player.getKeys()[i] + "%";
    }
    game.winGame(finalKey);

    Player player1(0);
    gameObject game2("nume", 3, player1);
    game.start();
    return 0;
}
