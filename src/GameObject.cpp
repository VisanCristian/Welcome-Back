#include "../headers/GameObject.h"
#include "../headers/Result.h"
#include "../headers/GameError.h"
#include "../headers/ConstructorError.h"
#include "../headers/InternalError.h"
#include <iostream>

GameObject::GameObject() : keyPrice(0), puzzleNr(1), milestone(1) {}

GameObject::~GameObject() = default;

GameObject& GameObject::getInstance() {
    static GameObject instance;
    return instance;
}

void GameObject::init(const std::string& gameName, const Player& p, const Computer& c) {
    name = gameName;
    player = p;
    computer = c;
    milestone = 1;
    puzzleNr = 1;
    setKeyPrice();
    std::cout << "Game Started! In order to find out the truth about your brother you have to find all the keys by solving the puzzles. \n" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const GameObject& obj) {
    os << "Game Object: " << obj.name << "\n";
    os << "Currently on milestone: " << obj.milestone << "\n";
    os << "Currently you have to solve the puzzle nr : " << obj.puzzleNr << "\n";
    return os;
}

void GameObject::checkPoint() {
    if (player.getPoints() < keyPrice) {
        gameOver("You don't have enough points to buy a key!");
        exit(1);
    }

    Result<std::string, GameError> keyResult = computer.getKey();
    if (!keyResult.isOk()) {
        gameOver(keyResult.getErr().what());
        return;
    }

    const std::string &key = keyResult.getOk();
    player.setPoints(player.getPoints() - keyPrice);
    player.addKey(key);
    setKeyPrice();
    std::cout << "You have succesfully completed this milestone and bought key #" << milestone << " : " << key << std::endl;
    milestone++;
}

void GameObject::gameOver(const std::string &reason) {
    std::cout << "Game Over! Reason: " << reason << std::endl;
    exit(0);
}

void GameObject::winGame(const std::string& finalKey) {
    std::cout << "Use this code to decrypt the files your brother left you... TO BE CONTINUED..." << std::endl;
    std::cout << "Final Key: " << finalKey << std::endl;
    exit(0);
}

void GameObject::setKeyPrice() {
    const std::unordered_map<int, int> keyPrices {
        {1, 700},
        {2, 800},
        {3, 900},
        {4, 1000},
        {5, 1100},
        {6, 1200}
    };

    const auto it = keyPrices.find(milestone);
    if (it == keyPrices.end()) {
        throw GameError("GameObject::setKeyPrice - invalid milestone " + std::to_string(milestone));
    }
    keyPrice = it->second;
}

void GameObject::start() {
    try {
        std::cout << "Pentru a completa jocul trebuie sa rezolvi puzzle-uri pentru a obtine puncte ca sa poti cumpara cheile de la final de milestone." << std::endl;
        std::cout << "De-a lungul acestor milestone-uri, se pot spawna killeri la intervale random (multiplii de 5). Desi sunt random, vei primi o avertizare cu maxim 10 minute inainte de aparitie." << std::endl;
        std::cout << "Ai 2 optiuni: sa rezolvi un puzzle / astepti 5 minute. Fiecare din optiuni va adauga 5 minute la timer, insa, daca se spawneaza un killer si nu ai ales optiunea sa astepti, la urmatoarea alegere vei pierde automat." << std::endl;
        std::cout << "OPtiunea de a extrage informatii despre fiecare inamic este gratis (nu adauga la timer)" << std::endl;
        std::cout << "BAFTA!" << std::endl;
        while (true) {
            int wrongChoice = 0;
            computer.eventLoop(milestone, player, wrongChoice);
            if (wrongChoice == 1) {
                gameOver("You lost the game!");
            }
            std::cout << "The milestone is over and the player has " << player.getPoints() << " points." << std::endl;
            checkPoint();
            if (milestone == 7) {
                player.setFinalKey(join(player.getKeys(), "%"));
                winGame(player.getFinalKey());
                exit(0);
            }
        }
    } catch (const ConstructorError &e) {
        gameOver(e.what());
    } catch (const GameError &e) {
        gameOver(e.what());
    } catch (const InternalError &e) {
        gameOver(e.what());
    } catch (const std::exception &e) {
        gameOver(e.what());
    }
}

template std::string join<char>(const std::vector<char>&, const std::string&);
template std::string join<std::string>(const std::vector<std::string>&, const std::string&);
