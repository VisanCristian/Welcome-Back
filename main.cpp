#include <fstream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Objects/buttonsInOrder.h"
#include "Objects/gameObject.h"
#include "Objects/Player.h"
#include "Objects/Computer.h"
#include "Objects/Puzzle.h"
#include "Objects/tagZones.h"


using namespace std;

int main() {
    Player player1;              
    Computer computer;
    gameObject game("nume", player1, computer);
    game.start();

    return 0;
}
