#ifndef ZOORK_VINES_ROOM_H
#define ZOORK_VINES_ROOM_H

#include "Room.h"
#include <iostream>

class Vines : public Room {
public:
    Vines() : Room("Vines", 
    "The Vines store are full of potions.\n The store is only filled with one type of potion.\n There is what ressembles a lift.\n") {}
    
    void handleExamine(const std::string& object) const override;
    void handleEnterTime(const std::string &time) const;
    void setPassage(std::shared_ptr<Passage> passage){
        lift = passage;
    }

private:
    mutable int remainingAttemptsTime = 5;
    const std::string correctTime = "09:10:15";
    std::shared_ptr<Passage> lift;
};

#endif // ZOORK_VINES_ROOM_H
