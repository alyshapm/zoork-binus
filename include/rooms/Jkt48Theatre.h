#ifndef ZOORK_JKT48THEATRE_ROOM_H
#define ZOORK_JKT48THEATRE_ROOM_H

#include "Room.h"
#include <iostream>

class Jkt48Theatre : public Room {
public:
    Jkt48Theatre() : Room("JKT48 Theatre", 
    "The velvet curtains are drawn, revealing a dimly lit theater.\n"
    "Spotlight beams illuminate framed photos of JKT48 idols, their smiles radiating energy.\n"
    "A grand stage sits at the front of the room, its polished floor reflecting the faint light.") {
        auto potion = std::make_shared<Item>("Jkt48 Potion", "A weird looking liquid that could wield some powers...", ItemType::POTION, 0);
        addItem(potion);
    }
    
    void handleExamine(const std::string& object) const override;
};

#endif // ZOORK_JKT48THEATRE_ROOM_H
