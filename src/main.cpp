#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

#include <memory>
#include <iostream>

#include "FxB1.h"

int main() {
    std::shared_ptr<Room> startRoom = std::make_shared<FxB1>();

    ZOOrkEngine zoork(startRoom);

    zoork.run();

    return 0;
}

