#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

#include <memory>
#include <iostream>

void setupRoomsAndPassages(std::shared_ptr<Room>& start) {
    // Room definitions
    std::shared_ptr<Room> foodhall = std::make_shared<Room>("Food Hall",
                                    "The aroma of fried noodles and bubble tea fills the air. Students chatter and laugh as they line up at the food stalls. A giant vending machine stands in the corner, flashing neon lights."
                                    );
    std::shared_ptr<Room> vines = std::make_shared<Room>("Vines (FX FB)",
                                    "Overgrown vines block your path, their leaves rustling in the breeze. The air is thick with the scent of exotic flowers and... something slightly poisonous."
                                    );
    std::shared_ptr<Room> lobby = std::make_shared<Room>("FX Lobby",
                                    "The lobby is buzzing with activity. Students rush to classes, professors chat in hushed tones, and a giant digital billboard displays a cryptic message from Mr. Z."
                                    );

    // Create passages between rooms
    Passage::createBasicPassage(start.get(), foodhall.get(), "north", true);
    Passage::createBasicPassage(foodhall.get(), vines.get(), "east", true);
    Passage::createBasicPassage(vines.get(), lobby.get(), "south", true);
}


int main() {
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                                    "You find yourself in the dimly lit basement of BINUS FX.\n"
                                    "The air is damp, and the only sound is the faint hum of electrical equipment.\n"
                                    "A steel door blocks your exit."
                                    );

    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}

