#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include "Item.h"
#include "Enemy.h"
#include "Dice.h" // Assuming a Dice class is available for dice rolling

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

    // Combat functionality
    void attack(Enemy& enemy);
    bool defend(int enemyAttackBonus);
    bool isDefeated() const;
    int getHealth() const;

    void addItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> getItem(const std::string& itemName) const;
    std::shared_ptr<Item> removeItem(const std::string& itemName);
    void listInventory() const;
    void clearInventory();
    void checkItemDescription(const std::string& itemName) const;

    void equipItem(const std::string& itemName);
    void unequipItem(const std::string& itemName);
    std::shared_ptr<Item> getEquippedItem(const std::string& itemName) const;
    void listEquippedItems() const;

    void addStatusEffect(const std::string& effectName, const std::string& effectDescription);
    void removeStatusEffect(const std::string& effectName);
    void listStatusEffects() const;

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;
    std::vector<std::shared_ptr<Item>> inventory;
    std::unordered_map<std::string, std::shared_ptr<Item>> equippedItems;
    std::unordered_map<std::string, std::string> statusEffects;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()), attackBonus(2), damage(5), armorClass(15), health(100) {}

    int attackBonus; // Player's bonus to attack rolls
    int damage;      // Damage inflicted by the player
    int armorClass;  // Armor class of the player
    int health;      // Health points of the player
};

#endif // ZOORK_PLAYER_H
