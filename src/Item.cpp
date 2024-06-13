#include "Item.h"

Item::Item(const std::string& name, const std::string& description)
    : GameObject(name, description), type(ItemType::GENERIC), modifier(0) {}

Item::Item(const std::string& name, const std::string& description, std::shared_ptr<Command> command)
    : GameObject(name, description), useCommand(command), type(ItemType::GENERIC), modifier(0) {}

Item::Item(const std::string& name, const std::string& description, ItemType type, int modifier)
    : GameObject(name, description), type(type), modifier(modifier) {}

void Item::use() {
    if (useCommand) {
        useCommand->execute();
    } else {
        // Default use behavior
        if (type == ItemType::WEAPON) {
            std::cout << "Using " << getName() << " as a weapon with a modifier of " << modifier << ".\n";
        } else {
            std::cout << "Using " << getName() << ".\n";
        }
    }
}

void Item::setUseCommand(std::shared_ptr<Command> command) {
    useCommand = command;
}

ItemType Item::getType() const {
    return type;
}

int Item::getModifier() const {
    return modifier;
}
