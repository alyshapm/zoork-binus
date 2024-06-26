#ifndef ZOORK_VINES_ROOM_H
#define ZOORK_VINES_ROOM_H

#include "Room.h"
#include <iostream>

class Vines : public Room {
public:
    Vines() : Room("Vines", 
    "The Vines store is full of potions.\nThe store is only filled with one type of potion.\nThere is what resembles a lift.") {
        // Add potion to room
        auto potion = std::make_shared<Item>("Vines Potion", "A weird looking liquid that could wield some powers...", ItemType::POTION, 0);
        addItem(potion);
    }
    
    void handleExamine(const std::string& object) const override;
    void handleEnterTime(const std::string &time) const;
    void setPassage(std::shared_ptr<Passage> passage){
        lift = passage;
    }

private:
    mutable int remainingAttemptsTime = 3;
    const std::string correctTime = "09:10:15";
    std::shared_ptr<Passage> lift;
};

#endif // ZOORK_VINES_ROOM_H
