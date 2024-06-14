#ifndef ZOORK_LOBBY_ROOM_H
#define ZOORK_LOBBY_ROOM_H

#include "Room.h"
#include <iostream>

class Lobby : public Room {
public:
    Lobby() : Room("Lobby", 
    "The lobby is buzzing with activity. Students rush to classes,\n"
    "professors chat in hushed tones, and a giant digital billboard displays\n"
    "To the east is what seems like a gray wall.") {
        // Add crowbar to room
        auto flashlight = std::make_shared<Item>("Flashlight", "A handy flashlight, it might help you see through things.", ItemType::GENERIC);
        addItem(flashlight);
    }
    
    void handleExamine(const std::string& object) const override;
    void handleRead(const std::string &object) const;
    void handleTalk(const std::string &object) const override;
    void handleGetThroughSmoke() const;

    void setPassage(std::shared_ptr<Passage> passage){
        smoke = passage;
    }

private:
    std::shared_ptr<Passage> smoke;
};

#endif // ZOORK_LOBBY_ROOM_H
