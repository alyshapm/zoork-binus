#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"
#include "Item.h"
#include "Enemy.h"
#include "Dice.h"

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

    void reset();
    void finishGame();
    bool hasFinishedGame() const;
    
    // Combat functionality
    void attack(Enemy& enemy);
    bool defend(int enemyAttackBonus);
    void takeDamage(int damage);
    bool isDefeated() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getDamage() const;
    int getAttackModifier() const;

    void addItem(std::shared_ptr<Item> item);
    std::shared_ptr<Item> getItem(const std::string& itemName) const;
    std::shared_ptr<Item> removeItem(const std::string& itemName);
    const std::vector<std::shared_ptr<Item>>& getInventory() const;
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
    bool hasStatusEffect(const std::string &effectName) const;
    void clearStatusEffects();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;
    std::vector<std::shared_ptr<Item>> inventory;
    std::unordered_map<std::string, std::shared_ptr<Item>> equippedItems;
    std::unordered_map<std::string, std::string> statusEffects;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()), attackBonus(0), damage(6), armorClass(10), health(100), maxHealth(100) {}

    int attackBonus; // Player's bonus to attack rolls (add with modifier if weapon included)
    int damage;      // Number for roll (d6 damage)
    int armorClass;  // Armor class of the player 
    int health;      // Health points of the player
    int maxHealth;   // Max health of the player.
    bool gameFinished = false; // Checks if player has finished game
};

#endif // ZOORK_PLAYER_H
