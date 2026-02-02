#include <fstream>
#include <random>
#include "headers/ButtonsInOrder.h"
#include "headers/GameObject.h"
#include "headers/Player.h"
#include "headers/Computer.h"
#include "headers/Puzzle.h"
#include "headers/TagZones.h"
#include "headers/InvalidConfigFile.h"

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
        GameObject::getInstance().init("Game", player1, computer);
        GameObject::getInstance().start();
        return 0;
    } catch (const InvalidConfigFile &e) {
        cerr << "Invalid configuration: " << e.what() << '\n';
        return 1;
    } catch (const std::exception &e) {
        cerr << "Unexpected error: " << e.what() << '\n';
        return 2;
    }
}
