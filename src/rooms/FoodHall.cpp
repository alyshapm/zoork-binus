#include "FoodHall.h"

void FoodHall::handleExamine(const std::string &object) const
{
    if (object == "surroundings" || object == "environment")
    {
        std::cout << "The students seem friendly enough. Maybe you can ask them for some advice?\n"
                     "Or is the cashier a better choice...\n"
                     "A broken clock is hanging on the wall.\n";
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
        std::cout << "'I hear the master of this place lives on the top floor, he awaits the one that is worth his challenge.'\n"
        "You should talk to Franz, he knows better.\n";
    } else if (object == "franz") 
    {
        std::cout << "He hands you a weird liquid... the label reads 'healing'.\n" 
        "You might need it later.\n"
        "'You should talk to the cashier Bob, he knows a way up.'\n";
        std::shared_ptr<Item> potion = std::make_shared<Item>("Healing Potion", "It might be able to help you get over your injuries...", ItemType::POTION, 0);
        addItem(potion);
    }
    else if (object == "cashier" || object == "bob")
    {
        std::cout << "Going up is your choice.\n"
        "But be assured that the rumors that you have heard are true. Mr Z is awaiting...\n"
        "To go up, head west.\n" 
        "Btw do you know the time?\n";
    }
    else
    {
        std::cout << "You talk to " << object << ", but are answered with silence.\n";
    }
}
