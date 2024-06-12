#include "Vines.h"
#include "ZOOrkEngine.h"

bool continueExaminingV = false;

void Vines::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "The abundance of potions is uncountable..\n"
        "It would be easy for you to take one without anyone noticing...\n";
    } 
    else if (object == "clock" || object == "broken clock")
    {
       std::cout << "The broken clock shows 09:10:15\n";
    }
    else if (object == "elevator" || object == "lift")
    {
        std::cout << "You see a sturdy elevator door with a keypad next to it. The keypad seems to be waiting for input.\n";
    }
    else if (object == "keypad")
    {
        std::cout << "The keypad says: \"What is the time?\"\n";
        std::string input;
        continueExaminingV = true;
        do {
            std::cout << "Enter the time in HH:MM:SS format ('exit' to stop): ";
            std::getline(std::cin, input);
            if (input == "exit") {
                std::cout << "You decide to stop examining the keypad.\n";
                continueExaminingV = false;
            } else {
                handleEnterTime(input);
            }
        } while (continueExaminingV);
    }
    else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void Vines::handleEnterTime(const std::string &time) const
{
    const std::string correctTime = "09:10:15"; // Correct time for the keypad
    if (time == correctTime)
    {
        std::cout << "Correct! The elevator door opens, and you can now enter the elevator.\n";
        lift->unlock();
        continueExaminingV = false;
    }
    else
    {
        if (--remainingAttemptsTime > 0)
        {
            std::cout << "Incorrect time. You have " << remainingAttemptsTime << " attempt(s) remaining.\n";
        }
        else
        {
            std::cout << "Incorrect time. You've used all your attempts. The security system has activated, and the elevator is now locked.\n";
            continueExaminingV = false;
        }
    }
}