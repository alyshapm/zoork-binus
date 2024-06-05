#ifndef ZOORK_PASSAGE_H
#define ZOORK_PASSAGE_H

#include "Room.h"
#include <iostream>
#include <memory>

class Passage : public Location {
public:
    static void createBasicPassage(Room*, Room*, const std::string &, bool bidirectional = true, bool locked = false);

    Passage(const std::string &, const std::string &, Room*, Room*, bool locked = false);

    Passage(const std::string &, const std::string &, std::shared_ptr<Command>, Room*, Room*, bool locked = false);

    void setFrom(Room*);
    Room* getFrom() const;

    void setTo(Room*);
    Room* getTo() const;

    void lock(); // Method to lock the passage
    void unlock(); // Method to unlock the passage
    bool isLocked() const; // Method to check if the passage is locked

protected:
    static std::string oppositeDirection(const std::string &);
    Room* fromRoom;
    Room* toRoom;
    bool locked;
};

#endif //ZOORK_PASSAGE_H
