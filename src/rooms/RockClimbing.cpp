#include "RockClimbing.h"
#include <Player.h>
#include "ZOOrkEngine.h"
#include <thread> // waiting
#include <chrono> // time

void RockClimbing::handleExamine(const std::string &object) const
{
    if (object == "surroundings" || object == "environment")
    {
        std::cout << "At the base of the wall stands a staff member ready to greet you.\n";
    }
    else
    {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void RockClimbing::handleTalk(const std::string &object) const
{
    if (object == "staff member" || object == "staff")
    {
        std::cout << "'The rock climb is fun but dangerous be careful when you climb.'\n"
                     "(The staff member sighs) 'When was the last time someone made it to the top?'\n"
                     "'Eons ago I would say. Many have tried, but few have conquered it.'\n"
                     "'Be sure you're prepared before attempting the climb'\n";
    }
    else
    {
        std::cout << "You talk to the " << object << ", but are answered with silence.\n";
    }
}

void RockClimbing::handleClimbWall() const
{
    Player *player = Player::instance();
    int time = 2;
    if (player->hasStatusEffect("Strength"))
    {
        std::cout << "You approach the rock climbing wall, feeling a mix of excitement and trepidation.\n";

        std::cout << "The staff member's words echo in your mind: 'The rock climb is fun but dangerous, be careful when you climb.'\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "Gripping the first handhold, you begin your ascent. The initial climb is smooth, boosting your confidence.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "However, the holds soon become sparse and challenging. You stretch to grasp a distant rock, barely managing to hold on.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "Halfway up, your muscles start to burn. You pause, clinging to the wall, sweat dripping down your forehead.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "Taking a deep breath, you steady your nerves and continue.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "Higher and higher you climb, the ground below fading away. A gust of wind forces you to cling tighter, your heart racing.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "With determination, you push through the final stretch.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "At last, you reach the top, pulling yourself over the edge with a triumphant shout. The view is breathtaking,\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "a reward for your perseverance. You savor the victory, knowing you've conquered the challenge.\n";
        player->removeStatusEffect("Strength");
        wall->unlock();
    }
    else
    {
        std::cout << "You approach the rock climbing wall, feeling a mix of excitement and trepidation.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "Ignoring the staff member's warning, you decide to climb without proper preparation.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "Gripping the first handhold, you begin your ascent. The wall feels much tougher than expected.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "You stretch for a distant hold, but your grip is weak and slips easily.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "Your muscles burn with fatigue much sooner this time. You are halfway up, you realize you're in trouble...\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "A sudden slip! Your hand loses its grip, and you scramble to hold on, but it's too late.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "You fall, your heart racing, You hit the ground firmly...\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "Laying on the ground, taking a moment to catch your breath. The staff member gives you a knowing look.\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "'I told you to be prepared,' they say. 'Come back when you're ready.'\n";
        std::this_thread::sleep_for(std::chrono::seconds(time));

        std::cout << "You'll need more strength, might you find a booster somewhere...\n";
        return;
    }
}