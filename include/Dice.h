#ifndef ZOORK_DICE_H
#define ZOORK_DICE_H

class Dice {
public:
    static int roll(int numberOfSides);
private:
    static void initializeRandom();
    static bool initialized;
};

#endif // ZOORK_DICE_H
