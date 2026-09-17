#pragma once

#include "raylib.h"

class Player;
class Boss;

class CollisionSystem
{
public:
    Rectangle createPlayerCollisionBox(
        const Player& player,
        float drawWidth,
        float drawHeight
    );

    Rectangle createBossCollisionBox(
        const Boss& boss,
        float drawWidth,
        float drawHeight
    );

    void resolveCharacterCollision(
        Player& player,
        const Rectangle& playerCollision,
        const Rectangle& bossCollision
    );
};