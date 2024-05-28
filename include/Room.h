#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>
#include <memory>
#include <functional>

class Passage;

class Room : public Location {
public:
    Room(const std::string &, const std::string &);

    Room(const std::string &, const std::string &, std::shared_ptr<Command>);

    void addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& itemName);
    std::shared_ptr<Item> getItem(const std::string& itemName);
    std::shared_ptr<Item> retrieveItem(const std::string& itemName);


    void addPassage(const std::string &, std::shared_ptr<Passage>);

    void removePassage(const std::string &);

    std::shared_ptr<Passage> getPassage(const std::string &);

    void addCommand(const std::string& command, std::function<void()> action);
    void executeCommand(const std::string& command);
    
private:
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
    std::map<std::string, std::shared_ptr<Item>> items;

    // Define specific functions for interactions
    virtual void handleExamine(const std::string& object) const;
    virtual void handleTalk(const std::string& object) const;
    virtual void handleFight(const std::string& object) const;
    virtual void handleRead(const std::string& object) const;
    virtual void handleDrink(const std::string& object) const;
    virtual void handleClimb(const std::string& object) const;
    virtual void handleEscape(const std::string& object) const;
    virtual void handleGo(const std::string& object) const;
};

#endif // ZOORK_ROOM_H
