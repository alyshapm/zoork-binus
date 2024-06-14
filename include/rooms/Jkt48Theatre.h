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
        auto paper = std::make_shared<Item>("Paper", "Contains JKT48's sacred dance routine.. Do you need this?", ItemType::GENERIC);
        addItem(paper);
    }
    
    void handleExamine(const std::string& object) const override;
    void handleRead(const std::string& object) const override;
    void handleDance() override;
};

#endif // ZOORK_JKT48THEATRE_ROOM_H
