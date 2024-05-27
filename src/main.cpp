#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

#include <memory>
#include <iostream>

#include "FxB1.h"

int main() {
    std::shared_ptr<Room> start = std::make_shared<FxB1>();

    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}

