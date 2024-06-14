#include "Jkt48Theatre.h"
#include "Utilities.h"
#include "ZOOrkEngine.h"

void Jkt48Theatre::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        if (backstage->isLocked()) {
            std::cout << "The vast theatre is empty, save for the stage and photos surrounding you.\n"
                  << "Behind the stage, large heavy red curtains cover the backstage.\n"
                  << "Below you, you see a paper taped flat to the floor.\n";
        } else {
            std::cout << "The vast theatre is empty, save for the stage and photos surrounding you.\n"
                  << "Behind the stage, large heavy red curtains parted to reveal the backstage.\n"
                  << "Below you, you see a paper taped flat to the floor.\n";
        }
    } else if (object == "photos" || object == "photo") {
        std::cout << "The photos depict various JKT48 members, each with a unique pose and costume.\n"
                  << "Their names and accomplishments are etched in small plaques below each photo.\n";
    } else if (object == "stage") {
        std::cout << "The stage is empty, but a microphone stand and a few musical instruments rest in the corner.\n"
        "The spotlight seems to beckon you towards the center.\n";
    } else if (object == "paper") {
        std::cout << "The paper describes an old dance routine of JKT48. You wonder what would happen if you dance on stage to it. \n ";
    } else if (object == "curtain" || object == "curtains") {
        if (backstage->isLocked()) {
            std::cout << "The curtains are too heavy to be moved. They seem to add a sense of elegance to the stage.\n";
        } else {
            std::cout << "The curtains have parted. They reveal a passage to your north.\n";
        }
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void Jkt48Theatre::handleRead(const std::string& object) const {
    if (object == "paper") {
        std::cout << "JKT48 Sacred Dance Routine: \n";
        std::cout << "Right\n";
        std::cout << "Right\n";
        std::cout << "Down\n";
        std::cout << "Up\n";
    } else {
        std::cout << "You read the " << object << ", but find yourself unable to understand it.\n";
    }
}

void Jkt48Theatre::handleDance() {
    std::vector<std::string> danceMoves = {"right", "right", "down", "up"};
    std::vector<std::string> userMoves;

    std::cout << "Perform the dance routine by entering the correct moves (left, right, up, or down).\n";
    std::cout << "Example: 'Dance: Left' (Enter 'stop' to stop dancing.)\n";
    for (size_t i = 0; i < danceMoves.size(); ++i) {
        std::string input;
        std::cout << "Dance: ";
        std::getline(std::cin, input);

        if (makeLowercase(input) == "stop") {
            std::cout << "You stopped dancing.\n";
            return; // Exit the function
        }

        userMoves.push_back(makeLowercase(input));
    }

    if (userMoves == danceMoves) {
        std::cout << "Congratulations! You've performed the JKT48 dance successfully!\n";
        std::shared_ptr<Item> potion = std::make_shared<Item>("JKT48 Potion", "A weird looking liquid that could wield some powers...", ItemType::POTION, 0);
        addItem(potion);
        std::cout << "A potion appears out of thin air! The label reads JKT48 Potion..\n";
        std::cout << "The curtains begin to move on their own, revealing an open doorway to your north..\n";
        backstage->unlock(); 
    } else {
        std::cout << "You improvised the dance. Nothing happens.\n";
    }
}

