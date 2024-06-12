#include "FoodHall.h"

void FoodHall::handleExamine(const std::string &object) const
{
    if (object == "surroundings" || object == "environment")
    {
        std::cout << "The students seem friendly enough. Maybe you can ask them for some advice?\n"
                     "Or is the cashier a better choice…\n"
                     "A broken clock  is hanging on the wall.";
    }
    else if (object == "clock")
    {
       std::cout << "The clock shows 09:10:15\n";
    }
    else
    {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void FoodHall::handleTalk(const std::string &object) const
{
    if (object == "students" || object == "student")
    {
        std::cout << "I hear the master of this place lives on the top floor, he awaits the one that is worth his challenge. You should talk to the cashier Bob, he knows a way up.\n";
    }
    else if (object == "cashier" || object == "Bob")
    {
        std::cout << "Going up is your choice but be assured that the rumors that you have heard are true. Mr Z is awaiting…\n"
        "Head west.\n"; 
        "Btw do you know the time?\n";
    }
    else
    {
        std::cout << "You talk to the " << object << ", but are answered with silence.\n";
    }
}
