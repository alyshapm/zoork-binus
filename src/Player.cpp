#include "Player.h"
#include "Utilities.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::attack(Enemy& enemy) {
    int roll = Dice::roll(20); // Assuming a 20-sided dice is used
    if (roll + attackBonus >= enemy.getArmorClass()) {
        // The attack hits
        enemy.takeDamage(Dice::roll(6) + damage); // Assuming a six-sided dice is used for damage
        std::cout << "You hit the " << enemy.getName() << "!\n";
    } else {
        std::cout << "You missed the " << enemy.getName() << "!\n";
    }
}

bool Player::defend(int enemyAttackBonus) {
    int roll = Dice::roll(20); // Assuming a 20-sided dice is used
    return roll + armorClass >= enemyAttackBonus;
}

int Player::getHealth() const {
    return health;
}

int Player::getDamage() const {
    return damage;
}

void Player::takeDamage(int damage) {
    health -= damage;
}

int Player::getAttackModifier() const {
    return attackBonus;
}

void Player::addItem(std::shared_ptr<Item> item) {
    inventory.push_back(item);
    std::cout << "You added " << item->getName() << " to your inventory.\n";
}

std::shared_ptr<Item> Player::getItem(const std::string& itemName) const {
    std::string itemNameLower = makeLowercase(itemName);
    for (const auto& item : inventory) {
        if (makeLowercase(item->getName()) == itemNameLower) {
            return item;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Player::removeItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == itemName) {
            std::shared_ptr<Item> item = *it;
            inventory.erase(it);
            std::cout << "You removed " << itemName << " from your inventory.\n";
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

void Player::clearInventory() {
    inventory.clear();
    std::cout << "Your inventory has been cleared.\n";
}

void Player::checkItemDescription(const std::string& itemName) const {
    for (const auto& item : inventory) {
        if (item->getName() == itemName) {
            std::cout << "Description of " << itemName << ": " << item->getDescription() << "\n";
            return;
        }
    }
    std::cout << "Item " << itemName << " not found in your inventory.\n";
}

void Player::equipItem(const std::string& itemName) {
    auto item = getItem(itemName);
    if (item) {
        // Check if the player already has an item equipped
        if (!equippedItems.empty()) {
            // If so, unequip the currently equipped item
            auto equippedItem = equippedItems.begin()->first;
            unequipItem(equippedItem);
        }
        equippedItems[itemName] = item;
        std::cout << "You have equipped the " << itemName << ".\n";
        if (item->getType() == ItemType::WEAPON) {
            attackBonus += item->getModifier();
        }
    } else {
        std::cout << "You don't have a " << itemName << " to equip.\n";
    }
}

void Player::unequipItem(const std::string& itemName) {
    auto it = equippedItems.find(itemName);
    if (it != equippedItems.end()) {
        equippedItems.erase(it);
        std::shared_ptr<Item> item = it->second;
        if (item->getType() == ItemType::WEAPON) {
            attackBonus -= item->getModifier();
        }
        std::cout << "You have unequipped the " << itemName << ".\n";
    } else {
        std::cout << "You don't have a " << itemName << " equipped.\n";
    }
}

std::shared_ptr<Item> Player::getEquippedItem(const std::string& itemName) const {
    auto it = equippedItems.find(itemName);
    if (it != equippedItems.end()) {
        return it->second;
    }
    return nullptr;
}

void Player::listEquippedItems() const {
    std::cout << "You have equipped:\n";
    for (const auto& item : equippedItems) {
        std::cout << "- " << item.first << "\n";
    }
}

void Player::addStatusEffect(const std::string& effectName, const std::string& effectDescription) {
    statusEffects[effectName] = effectDescription;
    std::cout << "Status effect added: " << effectName << "\n";
}

void Player::removeStatusEffect(const std::string& effectName) {
    statusEffects.erase(effectName);
    std::cout << "Status effect removed: " << effectName << "\n";
}

void Player::listStatusEffects() const {
    std::cout << "Current status effects:\n";
    for (const auto& effect : statusEffects) {
        std::cout << "- " << effect.first << ": " << effect.second << "\n";
    }
}

bool Player::isDefeated() const {
    return health <= 0;
}