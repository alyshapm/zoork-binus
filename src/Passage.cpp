#include "Passage.h"

#include <utility>
#include "PassageDefaultEnterCommand.h"

std::string Passage::oppositeDirection(const std::string &s) {
    if (s == "north") return "south";
    else if (s == "south") return "north";
    else if (s == "east") return "west";
    else if (s == "west") return "east";
    else if (s == "up") return "down";
    else if (s == "down") return "up";
    else if (s == "in") return "out";
    else if (s == "out") return "in";
    else return "unknown_direction";
}

void Passage::createBasicPassage(const std::string& name, const std::string& description, Room* from, Room* to, const std::string &direction, bool bidirectional, bool locked) {
    auto temp1 = std::make_shared<Passage>(name, description, from, to, locked);
    from->addPassage(direction, temp1);
    if (bidirectional) {
        auto temp2 = std::make_shared<Passage>(name, description, to, from, false);
        to->addPassage(oppositeDirection(direction), temp2);
    }
}

Passage::Passage(const std::string &n, const std::string &d, Room* from, Room* to, bool locked)
    : Location(n, d), fromRoom(from), toRoom(to), locked(locked) {
    setEnterCommand(std::make_shared<PassageDefaultEnterCommand>(this));
}

Passage::Passage(const std::string &n, const std::string &d, std::shared_ptr<Command> c, Room* from, Room* to, bool locked)
    : Location(n, d, std::move(c)), fromRoom(from), toRoom(to), locked(locked) {}

void Passage::setFrom(Room* r) {
    fromRoom = r;
}

Room* Passage::getFrom() const {
    return fromRoom;
}

void Passage::setTo(Room* r) {
    toRoom = r;
}

Room* Passage::getTo() const {
    return toRoom;
}

void Passage::lock() {
    locked = true;
}

void Passage::unlock() {
    locked = false;
}

bool Passage::isLocked() const {
    return locked;
}
