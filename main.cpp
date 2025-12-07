#include <fstream>
#include <random>
#include "Objects/buttonsInOrder.h"
#include "Objects/gameObject.h"
#include "Objects/Player.h"
#include "Objects/Computer.h"
#include "Objects/Puzzle.h"
#include "Objects/tagZones.h"
#include "Objects/GameErrors.h"


using namespace std;

int main() {

    try {
        std::ifstream fin("tastatura.txt");
        if (!fin) {
            throw InvalidConfigFile("Could not open tastatura.txt");
        }

        int difficulty;
        if (!(fin >> difficulty)) {
            throw InvalidConfigFile("Could not read difficulty from tastatura.txt");
        }
        if (difficulty < 1 || difficulty > 3) {
            throw InvalidConfigFile("Difficulty must be between 1 and 3");
        }

        Player player1;              
        Computer computer;
        gameObject game("nume", player1, computer);
        game.start();

        return 0;
    } catch (const InvalidConfigFile &e) {
        cerr << "Invalid configuration: " << e.what() << '\n';
        return 1;
    } catch (const std::exception &e) {
        cerr << "Unexpected error: " << e.what() << '\n';
        return 2;
    }
}
