#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include "Item.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

class Player : public Character {
public:
    static Player *instance() {
        if (!playerInstance) {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room*);
    Room* getCurrentRoom() const;

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

    // Inventory management
    void addItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> getItem(const std::string& itemName) const;
    std::shared_ptr<Item> removeItem(const std::string& itemName);
    void listInventory() const;
    void clearInventory();
    void checkItemDescription(const std::string& itemName) const;

    // Equipment management
    void equipItem(const std::string& itemName);
    void unequipItem(const std::string& itemName);
    std::shared_ptr<Item> getEquippedItem(const std::string& itemName) const;
    void listEquippedItems() const;

    // Status effects management
    void addStatusEffect(const std::string& effectName, const std::string& effectDescription);
    void removeStatusEffect(const std::string& effectName);
    void listStatusEffects() const;

private:
    static Player *playerInstance;
    Room* currentRoom;
    std::vector<std::shared_ptr<Item>> inventory;
    std::unordered_map<std::string, std::shared_ptr<Item>> equippedItems;
    std::unordered_map<std::string, std::string> statusEffects;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}
};

#endif //ZOORK_PLAYER_H
