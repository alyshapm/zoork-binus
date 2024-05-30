#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

#include <memory>
#include <iostream>

#include "FxB1.h"
#include "KanSup.h"

int main() {
    std::shared_ptr<Room> startRoom = std::make_shared<FxB1>();
    std::shared_ptr<Room> kansupRoom = std::make_shared<KanSup>();

    Passage::createBasicPassage(startRoom.get(), kansupRoom.get(), "up", true);

    ZOOrkEngine zoork(startRoom);

    zoork.run();

    return 0;
}

