#ifndef ZOORK_LOBBY_ROOM_H
#define ZOORK_LOBBY_ROOM_H

#include "Room.h"
#include <iostream>

class Lobby : public Room {
public:
    Lobby() : Room("Lobby", 
    "The lobby is buzzing with activity. Students rush to classes,\n"
    "professors chat in hushed tones, and a giant digital billboard displays\n"
    "a cryptic message from Mr. Z.") {}
    
    void handleExamine(const std::string& object) const override;
    void handleTalk(const std::string& object) const override;
};

#endif // ZOORK_LOBBY_ROOM_H
