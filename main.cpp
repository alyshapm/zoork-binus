#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

#include <memory>


int main() {
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                           "You are standing in an open field west of a white house, with a boarded front door.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                                    "You are facing the south side of a white house.  There is no door here, and all the windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                                  "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");

    // New rooms below
    std::shared_ptr<Room> garden = std::make_shared<Room>("garden","You are in a lush garden full of fragrant flowers and buzzing bees.");
    std::shared_ptr<Room> tower = std::make_shared<Room>("tower", "The old stone tower looms above you, its top lost in the clouds.");
    std::shared_ptr<Room> cellar = std::make_shared<Room>("cellar", "You descend into the cool, damp cellar, noticing rows of vintage wines.");
    std::shared_ptr<Room> library = std::make_shared<Room>("library", "Books from floor to ceiling, the library smells of old leather and paper.");
    std::shared_ptr<Room> attic = std::make_shared<Room>("attic", "The attic is dusty and full of old memories and cobwebs.");
    std::shared_ptr<Room> lake = std::make_shared<Room>("lake", "The peaceful lake, bordered by reeds, reflects the sky above.");
    std::shared_ptr<Room> woods = std::make_shared<Room>("woods", "You are in the dark woods, a canopy of trees blocking the sky.");

    Passage::createBasicPassage(start.get(), south_of_house.get(), "south", true);
    Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "east", true);

    // Linking new rooms together
    Passage::createBasicPassage(start.get(), south_of_house.get(), "south", true);
    Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "east", true);
    Passage::createBasicPassage(behind_house.get(), garden.get(), "north", true);
    Passage::createBasicPassage(garden.get(), woods.get(), "east", true);
    Passage::createBasicPassage(behind_house.get(), tower.get(), "up", true);
    Passage::createBasicPassage(behind_house.get(), cellar.get(), "down", true);
    Passage::createBasicPassage(south_of_house.get(), library.get(), "up", true);
    Passage::createBasicPassage(south_of_house.get(), attic.get(), "up", true);
    Passage::createBasicPassage(behind_house.get(), lake.get(), "west", true);

    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
