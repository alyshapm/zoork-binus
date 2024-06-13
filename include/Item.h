#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "Command.h"
#include "GameObject.h"

#include <memory>
#include <string>

// Enum to define different types of items
enum class ItemType {
    GENERIC,
    WEAPON,
    POTION
};

class Item : public GameObject {
public:
    Item(const std::string &, const std::string &);
    Item(const std::string &, const std::string &, std::shared_ptr<Command>);
    Item(const std::string& name, const std::string& description, ItemType type, int modifier = 0);

    virtual void use();
    void setUseCommand(std::shared_ptr<Command>);

    ItemType getType() const;
    int getModifier() const;

protected:
    std::shared_ptr<Command> useCommand;
    ItemType type;
    int modifier; // Used for items like weapons to add a modifier
};

#endif //ZOORK_ITEM_H