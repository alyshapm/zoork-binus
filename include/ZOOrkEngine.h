#ifndef ZOORK_ENGINE_H
#define ZOORK_ENGINE_H

#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Location.h"
#include "Passage.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <cctype>


class ZOOrkEngine {
public:
    ZOOrkEngine(std::shared_ptr<Room> start);

    void run();

private:
    Player* player;
    bool gameOver = false;

    void handleGoCommand(std::vector<std::string> arguments);
    void handleLookCommand(const std::vector<std::string>& arguments);
    void handleTakeCommand(std::vector<std::string> arguments);
    void handleDropCommand(std::vector<std::string> arguments);
    void handleQuitCommand(std::vector<std::string> arguments);
    void handleExamineCommand(std::vector<std::string> arguments);
    void handleReadCommand(std::vector<std::string> arguments);
    void handleTalkCommand(std::vector<std::string> arguments);

    std::vector<std::string> tokenizeString(const std::string &input);
    std::string makeLowercase(std::string input);
    std::string concatenateArguments(const std::vector<std::string>& arguments);
};

#endif // ZOORK_ENGINE_H
