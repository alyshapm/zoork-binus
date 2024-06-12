#include "Dice.h"
#include <cstdlib>
#include <ctime>

bool Dice::initialized = false;

void Dice::initializeRandom() {
    if (!initialized) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        initialized = true;
    }
}

int Dice::roll(int numberOfSides) {
    initializeRandom();
    return (std::rand() % numberOfSides) + 1;
}
