#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

#include <memory>
#include <iostream>

#include "FxB1.h"
#include "KanSup.h"
#include "FoodHall.h"
#include "Vines.h"
#include "Lobby.h"
#include "Sederhana.h"
#include "RockClimbing.h"
#include "Jkt48Theatre.h"
#include "Skorz.h"
#include "BinusFX.h"

int main() {
    while (true) {
        std::shared_ptr<Room> startRoom = std::make_shared<FxB1>();
        std::shared_ptr<Room> kansupRoom = std::make_shared<KanSup>();
        std::shared_ptr<Room> foodhallRoom = std::make_shared<FoodHall>();
        std::shared_ptr<Room> vinesRoom = std::make_shared<Vines>();
        std::shared_ptr<Room> fxLobbyRoom = std::make_shared<Lobby>();
        std::shared_ptr<Room> sederhanaRoom = std::make_shared<Sederhana>();
        std::shared_ptr<Room> rockClimbingRoom = std::make_shared<RockClimbing>();
        std::shared_ptr<Room> jkt48TheatreRoom = std::make_shared<Jkt48Theatre>();
        std::shared_ptr<Room> skorzRoom = std::make_shared<Skorz>();
        std::shared_ptr<Room> binusFXRoom = std::make_shared<BinusFX>();

        // create stairs from fxb1 to kansup
        Passage::createBasicPassage("Staircase",
            "A staircase that leads to another room.",
            startRoom.get(), kansupRoom.get(), "up", true, true);

        std::shared_ptr<Passage> staircase = startRoom->getPassage("up");
        std::static_pointer_cast<FxB1>(startRoom)->setPassage(staircase);

        // create vent from kansup to FH
        Passage::createBasicPassage("Vent",
            "A vent that leads to another room.",
            kansupRoom.get(), foodhallRoom.get(), "up", true, true);

        std::shared_ptr<Passage> vent = kansupRoom->getPassage("up");
        std::static_pointer_cast<KanSup>(kansupRoom)->setPassage(vent);

        Passage::createBasicPassage("Basement Floor",
            "A pathway to other stores.",
            foodhallRoom.get(), vinesRoom.get(), "west", true, false);

        // create lift from vines to lobby
        Passage::createBasicPassage("Lift",
            "An elevator that takes you to another floor.",
            vinesRoom.get(), fxLobbyRoom.get(), "up", true, true);

        std::shared_ptr<Passage> lift = vinesRoom->getPassage("up");
        std::static_pointer_cast<Vines>(vinesRoom)->setPassage(lift);

        Passage::createBasicPassage("1st Floor East",
            "A pathway to other stores.",
            fxLobbyRoom.get(), sederhanaRoom.get(), "east", true, true);

        std::shared_ptr<Passage> smoke = fxLobbyRoom->getPassage("east");
        std::static_pointer_cast<Lobby>(fxLobbyRoom)->setPassage(smoke);

        Passage::createBasicPassage("1st Floor North",
            "A pathway to other stores.",
            sederhanaRoom.get(), rockClimbingRoom.get(), "north", true, false);

        Passage::createBasicPassage("Climbing Wall",
            "A hike to the theatre.",
            rockClimbingRoom.get(), jkt48TheatreRoom.get(), "up", true, true);

        std::shared_ptr<Passage> wall = rockClimbingRoom->getPassage("up");
        std::static_pointer_cast<RockClimbing>(rockClimbingRoom)->setPassage(wall);

        Passage::createBasicPassage("Backstage",
            "The backstage passages behind the theatre stage",
            jkt48TheatreRoom.get(), skorzRoom.get(), "north", true, true);

        std::shared_ptr<Passage> backstage = jkt48TheatreRoom->getPassage("north");
        std::static_pointer_cast<Jkt48Theatre>(jkt48TheatreRoom)->setPassage(backstage);

        Passage::createBasicPassage("Elevator",
            "An elevator that leads you to the highest floor",
            skorzRoom.get(), binusFXRoom.get(), "up", true, true);

        std::shared_ptr<Passage> elevator = skorzRoom->getPassage("up");
        std::static_pointer_cast<Skorz>(skorzRoom)->setPassage(elevator);

        ZOOrkEngine zoork(startRoom);
        zoork.run();

        if (!zoork.isRestartRequested()) {
            break; // Exit the loop if restart is not requested
        }
    }

    return 0;
}
