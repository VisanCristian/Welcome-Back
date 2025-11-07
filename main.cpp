#include <fstream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Objects/buttonsInOrder.h"
#include "Objects/gameObject.h"
#include "Objects/Player.h"
#include "Objects/Puzzle.h"
#include "Objects/tagZones.h"


using namespace std;

int main() {
    Player player1(0);
    gameObject game2("nume", 3, player1);
    game2.start();

    return 0;
}