#ifndef ZOORK_BINUSFX_ROOM_H
#define ZOORK_BINUSFX_ROOM_H

#include "Room.h"
#include <iostream>

class BinusFX : public Room {
public:
    BinusFX() : Room("Binus FX", 
    "The elevator doors slide open, revealing a dimly lit, high-tech laboratory.\n"
    "Strange contraptions hum and whir, casting eerie shadows on the walls. \n"
    "At the far end of the room, a figure silhouetted against a massive computer screen turns to face you.\n"
    "It's Dr. Z, his eyes glinting with a mix of madness and brilliance.") {}
};

#endif // ZOORK_BINUSFX_ROOM_H
