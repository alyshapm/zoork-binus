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
    static ZOOrkEngine& instance();

    void run();

    void requestRestart(std::shared_ptr<Room> start = nullptr);

private:
    Player* player;
    bool gameOver = false;
    std::shared_ptr<Room> startRoom;

    void handleGoCommand(std::vector<std::string> arguments);
    void handleLookCommand(const std::vector<std::string>& arguments);
    void handleTakeCommand(std::vector<std::string> arguments);
    void handleDropCommand(std::vector<std::string> arguments);
    void handleQuitCommand(std::vector<std::string> arguments);
    void handleExamineCommand(std::vector<std::string> arguments);
    void handleReadCommand(std::vector<std::string> arguments);
    void handleTalkCommand(std::vector<std::string> arguments);
    void handleRestartCommand(std::vector<std::string> arguments);
    void handleRoomRestartCommand(std::vector<std::string> arguments, std::shared_ptr<Room> start);
    void handleInventoryCommand();
    void handleInspectCommand(std::vector<std::string> arguments);
    void handleEquipCommand(const std::vector<std::string>& arguments);
    void handleUnequipCommand(const std::vector<std::string>& arguments);
    void handleStatusCommand();
    void handleOpenCommand(std::vector<std::string> arguments);
    void handleFightCommand(std::vector<std::string> arguments);
    void handleDrinkCommand(std::vector<std::string> arguments);
    void handleHelpCommand();
    void handleStatsCommand();
    void handleDeathCommand();
    void handleDanceCommand();

    std::vector<std::string> tokenizeString(const std::string &input);
    std::string concatenateArguments(const std::vector<std::string>& arguments);

    static ZOOrkEngine* instance_;
};

#endif // ZOORK_ENGINE_H
