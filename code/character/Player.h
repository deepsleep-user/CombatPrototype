#pragma once

#include "Character.h"

#include <iostream>

class Player : public Character
{
public:
    Player(
        int initialHP,
        float initialPosture,
        int initialAttackPower,
        int initialDefense,
        float initialX,
        float initialY,
        float initialMoveSpeed
    )
        : Character(
            initialHP,
            initialPosture,
            initialAttackPower,
            initialDefense,
            initialX,
            initialY,
            initialMoveSpeed
        )
    {
    }

    void showStatus() const override
    {
        std::cout << "=== Player ===\n";
        Character::showStatus();
    }
};