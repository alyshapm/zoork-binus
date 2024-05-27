//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"
#include "Room.h"
#include <iostream>

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::addItem(std::shared_ptr<Item> item) {
    inventory.push_back(item);
    std::cout << item->getName() << " added to your inventory.\n";
}

std::shared_ptr<Item> Player::removeItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == itemName) {
            std::shared_ptr<Item> item = *it;
            inventory.erase(it);
            std::cout << itemName << " removed from your inventory.\n";
            return item;
        }
    }
    return nullptr;
}

void Player::listInventory() const {
    if (inventory.empty()) {
        std::cout << "Your inventory is empty.\n";
    } else {
        std::cout << "You are carrying:\n";
        for (const auto& item : inventory) {
            std::cout << "- " << item->getName() << "\n";
        }
    }
}