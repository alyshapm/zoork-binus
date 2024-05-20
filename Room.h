//
// Created by Richard Skarbez on 5/7/23.
//

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
   void removeItem(const std::string&);
   std::shared_ptr<Item> getItem(const std::string&);
   std::shared_ptr<Item> retrieveItem(const std::string& name);

//    Item* retrieveItem(const std::string&);
//    void addCharacter(Character*);
//    void removeCharacter(const std::string&);
//    Character* getCharacter(const std::string&);

    void addPassage(const std::string &, std::shared_ptr<Passage>);

    void removePassage(const std::string &);

    std::shared_ptr<Passage> getPassage(const std::string &);

    void addCommand(const std::string& command, std::function<void()> action);
    void executeCommand(const std::string& command);

protected:
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
    std::map<std::string, std::shared_ptr<Item>> items; // Stores items by name

//    std::vector<Item*> items;
//    std::vector<Character*> characters;

    std::map<std::string, std::function<void()>> commands;
    
};


#endif //ZOORK_ROOM_H
