#ifndef ZOORK_FXB1_ROOM_H
#define ZOORK_FXB1_ROOM_H

#include "Room.h"
#include <iostream>

class FxB1 : public Room {
public:
    FxB1() : Room("FX B1", 
    "You find yourself in the dimly lit basement of BINUS FX.\n"
    "The air is damp, and the only sound is the faint hum of electrical equipment.\n"
    "A steel door blocks your exit.") {}
    
    void handleExamine(const std::string& object) const override;
    void handleTalk(const std::string& object) const override;
    void handleRead(const std::string& object) const override;
};

#endif // ZOORK_FXB1_ROOM_H
