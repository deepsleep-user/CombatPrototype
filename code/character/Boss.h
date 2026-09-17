#pragma once

#include "Character.h"

#include <iostream>

class Boss : public Character
{
public:
    Boss(
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
        std::cout << "=== Boss ===\n";
        Character::showStatus();
    }
};