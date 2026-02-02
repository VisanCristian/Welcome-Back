#include "../headers/Computer.h"
#include "../headers/GameObject.h"

#include <random>
#include <algorithm>
#include <fstream>
#include <utility>

#include "../headers/PuzzleFactory.h"
#include "../headers/ButtonsInOrder.h"
#include "../headers/TagZones.h"
#include "../headers/RememberNumbers.h"
#include "../headers/Lucas.h"
#include "../headers/Noir.h"
#include "../headers/Police.h"

Computer::Computer() = default;

Computer::Computer(const Computer& other)
    :newPuzzle(other.newPuzzle
                ? std::shared_ptr<Puzzle>(other.newPuzzle->clone().release())
                : nullptr) {}

Computer::~Computer() = default;

void swap(Computer& a, Computer& b) noexcept {
    using std::swap;
    swap(a.newPuzzle, b.newPuzzle);
}

Computer& Computer::operator=(Computer other) {
    swap(*this, other);
    return *this;
}

Result<std::string, GameError> Computer::getKey(){
    std::vector<char> keyChars;
    for (int i = 0; i < 10; i++) {
        keyChars.push_back(static_cast<char>('0' + i));
    }
    for (int i = 0; i < 6; i++) {
        keyChars.push_back(static_cast<char>('a' + i));
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(keyChars.begin(), keyChars.end(), gen);
    std::string key = join(keyChars, "");
    return Result<std::string, GameError>::OkResult(key);
}



Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError> Computer::generatePuzzle(int milestone) {

    std::ifstream fin("assets/PuzzleDecks");
    if (!fin) {
        return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(
                ConstructorError("Computer::generatePuzzle - could not open PuzzleDecks for reading"));
    }

    const std::string structure = "M" + std::to_string(milestone);
    std::vector<std::shared_ptr<Puzzle>> puzzles;
    std::vector<std::string> tiers;
    std::string tier;

    while (tier != structure) {
        if (!(fin >> tier)) {
            return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(
                    ConstructorError("Computer::generatePuzzle - failed while reading from PuzzleDecks"));
        }
    }

    for (int i = 0; i < 7; i++) {
        if (!(fin >> tier)) {
            return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(
                    ConstructorError("Computer::generatePuzzle - not enough tier entries for milestone"));
        }
        tiers.push_back(tier);
    }

    std::mt19937 gen1(std::random_device{}());
    std::shuffle(tiers.begin(), tiers.end(), gen1);

    for (int i = 0; i < 7; i++) {
        tier = tiers[i];
        if (tier == "T3") {
            try {
                puzzles.push_back(PuzzleFactory::createPuzzle("T3"));
            } catch (const ConstructorError& e) {
                return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(e);
            }
        } else {
            try {
                puzzles.push_back(PuzzleFactory::createPuzzle(tier));
            } catch (const ConstructorError& e) {
                return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(e);
            }
        }
    }

    if (puzzles.empty()) {
        return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::ErrResult(
                ConstructorError("Computer::generatePuzzle - no puzzles generated for milestone"));
    }

    std::mt19937 gen(std::random_device{}());
    std::shuffle(puzzles.begin(), puzzles.end(), gen);

    return Result<std::vector<std::shared_ptr<Puzzle>>, ConstructorError>::OkResult(puzzles);
}

void Computer::eventLoop(int milestone, Player& player, int& wrongChoice) {
    const auto puzzleResult = generatePuzzle(milestone);
    if (!puzzleResult.isOk()) {
        throw puzzleResult.getErr();
    }

    const auto &puzzles = puzzleResult.getOk();
    int timeFromLastKillerSpawn = 0;
    for (int i = 0; i < 7; i++) {
        

        if (wrongChoice == 1) {
            return;
        }
        int randomSpawnTimer;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(2, 5);
        randomSpawnTimer = dist(gen);
        randomSpawnTimer *= 5;

        int gameChoice;
    choices:
        std::cout << "Alegeti din urmatoarea lisa de optiuni: \n";
        if (randomSpawnTimer - timeFromLastKillerSpawn <= 10) {
            std::cout << "You feel something strange......\n";
        }
        std::cout << "1. Rezolva urmatorul puzzle \n";
        std::cout << "2. Asteapta 5 minute. \n";
        std::cout << "3. Explica reguli Noir \n";
        std::cout << "4. Explica reguli Lucas \n";
        std::cout << "5. Explica reguli Politie \n";
        std::cin >> gameChoice;
        
        

        if (gameChoice == 2) {
            timeFromLastKillerSpawn += 5;
        } else if (gameChoice == 3) {
            std::cout << "Reguli Noir: \n";
            std::cout << "Pentru a trece cu succes de NOIR trebuie sa stai cu spatele la el \n";
            goto choices;
        } else if (gameChoice == 4) {
            std::cout << "Reguli Lucas: \n";
            std::cout << "Pentru a trece cu succes de LUCAS trebuie sa te ascunzi \n";
            goto choices;
        } else if (gameChoice == 5) {
            std::cout << "Reguli Politie: \n";
            std::cout << "Pentru a trece cu succes de POLITIE trebuie sa schimbi conexiunea la alta retea. \n";
            goto choices;
        } else if (gameChoice != 1) {
            gameChoice = 1;
            std::cout << "Alegerea nu este una potrivita... se continua cu optiunea 1.\n";
        }

        if (timeFromLastKillerSpawn >= randomSpawnTimer) {
            timeFromLastKillerSpawn = 0;
            std::shared_ptr<Killer> k;
            int randomKiller;
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<int> dist(0, 2);
            randomKiller = dist(gen);
            if (randomKiller == 0) {
                k = std::make_shared<Lucas>();
            } else if (randomKiller == 1) {
                k = std::make_shared<Noir>();
            } else {
                k = std::make_shared<Police>();
            }
            if (gameChoice == 1) {
                wrongChoice = 1;
            }
            else {
                Option playerChoice = k->spawn();
                if (std::dynamic_pointer_cast<Noir>(k) && playerChoice != Option::Turn) {
                    wrongChoice = 1;
                    return;
                }
                if (std::dynamic_pointer_cast<Lucas>(k) && playerChoice != Option::Hide) {
                    wrongChoice = 1;
                    return;
                }
                if (std::dynamic_pointer_cast<Police>(k) && playerChoice != Option::ChangeConnection) {
                    wrongChoice = 1;
                    return;
                }
            }

            if (std::dynamic_pointer_cast<Police>(k)) {
                timeFromLastKillerSpawn = -5;
            }
        }

        if (gameChoice == 2) {
            continue;
        }

        newPuzzle = puzzles[i];
        timeFromLastKillerSpawn += 5;
        std::cout << "Puzzle-ul pe care trebuie sa-l rezolvi este: \n" << *newPuzzle << std::endl;

        if (std::dynamic_pointer_cast<ButtonsInOrder>(newPuzzle)) {
            std::cout << "Pentru a rezolva puzzle-ul trebuie sa apasati butoanele in ordinea crescatoare a numerelor care apar.\n" << std::endl;
        } else if (std::dynamic_pointer_cast<TagZones>(newPuzzle)) {
            std::cout << "Pentru a rezolva puzzle-ul trebuie sa formati zone din blocuri adiacente. 2 blocuri sunt adiacente daca sunt una langa alta(inclusiv pe diagonala)\n" << std::endl;
        } else if (std::dynamic_pointer_cast<RememberNumbers>(newPuzzle)) {
            std::cout << "Pentru a rezolva puzzle-ul trebuie sa rescrii numerele care au aparut pe ecran.\n" << std::endl;
        } else {
            throw GameError("Computer::eventLoop - invalid puzzle type");
        }

        newPuzzle->setAnswer(newPuzzle->getUserInput());

        if (newPuzzle->checkAnswer() == 1) {
            std::cout << "You have solved this puzzle. You have been awarded " << newPuzzle->getPoints() << " points." << std::endl;
            player.setPoints(player.getPoints() + newPuzzle->getPoints());
        } else {
            std::cout << "You have failed to solve the puzzle.";
        }
    }
}


