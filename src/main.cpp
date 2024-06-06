#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

#include <memory>
#include <iostream>

#include "FxB1.h"
#include "KanSup.h"
#include "FoodHall.h"

int main() {
    std::shared_ptr<Room> startRoom = std::make_shared<FxB1>();
    std::shared_ptr<Room> kansupRoom = std::make_shared<KanSup>();
    std::shared_ptr<Room> foodhallRoom = std::make_shared<FoodHall>();;

    Passage::createBasicPassage("Staircase",
        "A staircase that leads to another room.",
        startRoom.get(), kansupRoom.get(), "up", true, true);

    std::shared_ptr<Passage> staircase = startRoom->getPassage("up");
    std::static_pointer_cast<FxB1>(startRoom)->setDoor(staircase);

    ZOOrkEngine zoork(startRoom);

    zoork.run();

    return 0;
}
