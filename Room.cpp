//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"
#include "Item.h"

#include <utility>
#include <memory>

Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        passageMap.erase(it);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        return it->second;
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}


void Room::addItem(std::shared_ptr<Item> item) {
    items[item->getName()] = item;
}

void Room::removeItem(const std::string& name) {
    items.erase(name);
}

std::shared_ptr<Item> Room::getItem(const std::string& name) {
    auto it = items.find(name);
    if (it != items.end()) {
        return it->second;  // Return the shared_ptr directly
    }
    return nullptr;  // Return nullptr if the item is not found
}


std::shared_ptr<Item> Room::retrieveItem(const std::string& name) {
    auto it = items.find(name);
    if (it != items.end()) {
        std::shared_ptr<Item> item = it->second;
        items.erase(it);
        return item;
    }
    return nullptr;
}
