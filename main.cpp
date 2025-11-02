#include <fstream>
#include <random>

#include "Objects/buttonsInOrder.h"
#include "Objects/gameObject.h"
#include "Objects/Player.h"
#include "Objects/Puzzle.h"
#include "Objects/tagZones.h"


using namespace std;

int main() {

    std::ifstream fin("tastatura.txt");
    // Constructors:
    Player p1(2);
    gameObject game1("test", 1, p1);
    buttonsInOrder puzzle1(10);
    tagZones puzzle2(10);

    cout << p1 << endl << game1 << endl << puzzle1 << puzzle2;




   int difficulty, attempts;
    fin >> difficulty >> attempts;
    cout << difficulty << attempts << endl;
    Player player(attempts);
    gameObject game("game1", difficulty, player);

    for (int i = 0; i < game.getDifficulty(); i++) {
        //Puzzle puzzle("buttonsInOrder");
        tagZones puzzle(10);

        vector<int> userAnswer = puzzle.getAnswer();
        cout << "User Answer: \n";

        // Fail example
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 100);
        if (dist(gen) % 3 == 1) {
            userAnswer.resize(userAnswer.size(), -2);
        }

        for (unsigned long int j = 0; j < userAnswer.size(); j++) {
            cout << userAnswer[j] << " ";
        }

        puzzle.setAnswer(userAnswer);
        //cout << "Attempts:" << player.getAttemptsLeft();
        cout << puzzle;
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

    gameObject game3(game);
    cout << game3;

    game.winGame(finalKey);

    Player player1(0);
    gameObject game2("nume", 3, player1);
    game2.start();

    return 0;
}
