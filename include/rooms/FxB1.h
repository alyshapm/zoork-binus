#ifndef ZOORK_FXB1_ROOM_H
#define ZOORK_FXB1_ROOM_H

#include "Room.h"
#include <iostream>
#include <random>

class FxB1 : public Room {
public:
    FxB1() : Room("FX B1",
    "You find yourself in the dimly lit basement of BINUS FX.\n"
    "The air is damp, and the only sound is the faint hum of electrical equipment.\n"
    "A steel door blocks your exit.") {}

    void handleExamine(const std::string& object) const override;
    void handleTalk(const std::string& object) const override;
    void handleRead(const std::string& object) const override;
    void handleEnterPasscode(const std::string& passcode) const;

    private:
    mutable int remainingAttempts = 2;
    std::string correctPasscode;

    std::string generateRandomPasscode() {
        // Define the range of characters for the passcode
        const std::string passcodeChars = "0123456789";
        const int passcodeLength = 6;

        // Initialize random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, passcodeChars.size() - 1);

        // Generate random passcode
        std::string passcode;
        for (int i = 0; i < passcodeLength; ++i) {
            passcode += passcodeChars[dis(gen)];
        }

        return passcode;
    }
};

#endif // ZOORK_FXB1_ROOM_H
