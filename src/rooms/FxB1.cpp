#include "FxB1.h"
#include "ZOOrkEngine.h"

bool continueExamining = false;

void FxB1::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "You see a security guard asleep at his desk and a toolbox.\n"
                  << "Next to him, a door with a keypad. He's not doing a good job of guarding it..\n";
    } else if (object == "door") {
        if (door->isLocked()) {
            std::cout << "The door is locked, and there's a keypad next to it.\n";
        } else {
            std::cout << "The door is unlocked. A staircase awaits you.\n";
        }
    } else if (object == "toolbox") {
        std::cout << "It's unlocked and contains a rope, a sturdy crowbar, and a note.\n";
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
        if (correctPasscode.size() != 6) {
            std::cerr << "Error: Passcode length is incorrect.\n";
            std::cout << correctPasscode;
        }

        std::cout << "Shopping List:\n\n"
                  << "-" << correctPasscode[0] << " ripe apples, a tart delight\n"
                  << "-" << correctPasscode[1] << " juicy oranges, bursting with sunlight\n"
                  << "-" << correctPasscode[2] << " plump tomatoes, firm to the touch\n"
                  << "-" << correctPasscode[3] << " crisp carrots, offering a healthy crunch\n"
                  << "-" << correctPasscode[4] << " sweet mangoes, a tropical treat\n"
                  << "-" << correctPasscode[5] << " vibrant peppers, adding a spicy heat\n\n"
                  << "The fruits will open the way to a new realm.\n";

        return;
    } else {
        std::cout << "You read the " << object << ", but find yourself unable to understand it.\n";
    }
}

void FxB1::handleTalk(const std::string& object) const {
    if (object == "security guard" || object == "guard") {
        std::cout << "(Wakes up, groggy) \"Hey, you're not supposed to be down here! Get out before I call...\" (Falls back asleep)\n";
    } else {
        std::cout << "You talk to the " << object << ", but there's no response.\n";
    }
}

void FxB1::handleEnterPasscode(const std::string& passcode) const {
    if (passcode == correctPasscode) {
        std::cout << "Click! The door unlocks with a satisfying click. You can now go up.\n";
        door->unlock(); 
        continueExamining = false;
        
    } else {
        if (--remainingAttempts > 0) {
            std::cout << "Access Denied. Incorrect passcode. You have " << remainingAttempts << " attempt(s) remaining.\n";
        } else {
            std::cout << "Access Denied. You've used all your attempts. The security system has activated, and you hear footsteps approaching.\n"
                      << "You've been captured by the security guard!\n";
            continueExamining = false;
            ZOOrkEngine::instance().requestRestart();
        }
    }
}