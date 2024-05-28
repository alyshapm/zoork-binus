#include "FxB1.h"
#include "ZOOrkEngine.h"

bool continueExamining = false;

void FxB1::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "You see a security guard asleep at his desk and a toolbox.\n";
    } else if (object == "door") {
        std::cout << "The door is locked, and there's a keypad next to it.\n";
    } else if (object == "toolbox") {
        std::cout << "It's unlocked and contains a rope, a sturdy belt, and a note.\n";
    } else if (object == "keypad") {
        std::cout << "You examine the keypad.\n";
        std::string input;
        continueExamining = true;
        do {
            std::cout << "Enter the 6 numbers passcode ('exit' to continue examining surroundings): ";
            std::getline(std::cin, input);
            if (input == "exit") {
                std::cout << "You decide to keep looking around.\n";
                continueExamining = false;
            } else {
                handleEnterPasscode(input);
            }
    } while (continueExamining);
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void FxB1::handleRead(const std::string& object) const {
    if (object == "note") {
        std::cout << correctPasscode << std::endl;
        std::cout << "Shopping List:\n\n";
        std::cout << "-" << correctPasscode[0] << " ripe apples, a tart delight\n";
        std::cout << "-" << correctPasscode[1] << " juicy oranges, bursting with sunlight\n";
        std::cout << "-" << correctPasscode[2] << " plump tomatoes, firm to the touch\n";
        std::cout << "-" << correctPasscode[3] << " crisp carrots, offering a healthy crunch\n";
        std::cout << "-" << correctPasscode[4] << " sweet mangoes, a tropical treat\n";
        std::cout << "-" << correctPasscode[5] << " vibrant peppers, adding a spicy heat\n\n";
        std::cout << "The fruits will open the way to a new realm.\n";
    } else {
        std::cout << "You read the " << object << ", but find yourself unable to understand it.\n";
    }
}

void FxB1::handleTalk(const std::string& object) const {
    if (object == "security guard") {
        std::cout << "(Wakes up, groggy) \"Hey, you're not supposed to be down here! Get out before I call...\" (Falls back asleep)\n";
    } else {
        std::cout << "You talk to the " << object << ", but there's no response.\n";
    }
}

void FxB1::handleEnterPasscode(const std::string& passcode) const {
    if (passcode == correctPasscode) {
        std::cout << "Click! The door unlocks with a satisfying click. You ascend the stairs, leaving the musty basement behind.\n";
        continueExamining = false;
        // move
    } else {
        if (remainingAttempts > 0) {
            std::cout << "Access Denied. Incorrect passcode. You have " << remainingAttempts << " attempt(s) remaining.\n";
            remainingAttempts--;
        } else {
            std::cout << "Access Denied. You've used all your attempts. The security system has activated, and you hear footsteps approaching.\n";
            std::cout << "You've been captured by the security guard!\n";
            continueExamining = false;
            ZOOrkEngine::instance().requestRestart();
        }
    }
}

