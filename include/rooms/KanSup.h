#ifndef ZOORK_KANSUP_ROOM_H
#define ZOORK_KANSUP_ROOM_H

#include "Room.h"
#include <iostream>

class KanSup : public Room {
public:
    KanSup() : Room("Kantin Supir", 
    "You find yourself in an empty food court. There aren't any doors besides the one you used to enter..") {}
    
    void handleExamine(const std::string& object) const override;
    void handleTalk(const std::string& object) const override;
    void handleRead(const std::string& object) const override;
};

#endif // ZOORK_KANSUP_ROOM_H
