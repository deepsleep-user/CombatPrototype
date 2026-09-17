#include "Character.h"

#include <iostream>
#include <algorithm>
#include <cmath>

Character::Character(
    int initialHP,
    float initialPosture,
    int initialAttackPower,
    int initialDefense,
    float initialX,
    float initialY,
    float initialMoveSpeed
)
    : hp(initialHP),
      posture(initialPosture),
      attackPower(initialAttackPower),
      defense(initialDefense),
      x(initialX),
      y(initialY),
      moveSpeed(initialMoveSpeed)
{
}

void Character::showStatus() const
{
    std::cout << "HP: " << hp << '\n';
    std::cout << "Posture: " << posture << '\n';
    std::cout << "Attack Power: "
              << attackPower << '\n';
    std::cout << "Defense: "
              << defense << '\n';
}

void Character::showState() const
{
    switch (state)
    {
        case CharacterState::Idle:
            std::cout << "Idle\n";
            break;

        case CharacterState::Attacking:
            std::cout << "Attacking\n";
            break;

        case CharacterState::Defending:
            std::cout << "Defending\n";
            break;

        case CharacterState::Rolling:
            std::cout << "Rolling\n";
            break;

        case CharacterState::GuardBroken:
            std::cout << "GuardBroken\n";
            break;

        case CharacterState::Dead:
            std::cout << "Dead\n";
            break;
    }
}

void Character::die()
{
    state = CharacterState::Dead;

    guardBreakTimer = 0.0f;
    rollTimer = 0.0f;
    attackTimer = 0.0f;
}

void Character::takeDamage(int damage)
{
    if (state == CharacterState::Dead)
    {
        return;
    }

    if (state == CharacterState::Rolling)
    {
        return;
    }

    int actualDamage =
        std::max(0, damage - defense);

    if (state == CharacterState::Defending)
    {
        increasePosture(BLOCK_POSTURE_COST);
    }
    else
    {
        hp = std::max(
            0,
            hp - actualDamage
        );
    }

    if (hp == 0)
    {
        die();
    }
}

void Character::attack()
{
    if (state != CharacterState::Idle)
    {
        return;
    }

    state = CharacterState::Attacking;
    attackTimer = ATTACK_DURATION;
}

void Character::increasePosture(float amount)
{
    if (state == CharacterState::Dead)
    {
        return;
    }

    posture =
        std::min(
            posture + amount,
            MAX_POSTURE
        );

    if (posture >= MAX_POSTURE)
    {
        guardBreak();
    }
}

void Character::defend()
{
    if (state == CharacterState::Idle)
    {
        state =
            CharacterState::Defending;
    }
}

void Character::stopDefending()
{
    if (state ==
        CharacterState::Defending)
    {
        state =
            CharacterState::Idle;
    }
}

void Character::guardBreak()
{
    state =
        CharacterState::GuardBroken;

    guardBreakTimer =
        GUARD_BREAK_DURATION;
}

void Character::roll()
{
    if (state != CharacterState::Idle &&
        state != CharacterState::Defending)
    {
        return;
    }

    state =
        CharacterState::Rolling;

    rollTimer =
        ROLL_DURATION;
}

void Character::update(float deltaTime)
{
    if (state == CharacterState::Dead)
    {
        return;
    }

    if (state ==
        CharacterState::Defending)
    {
        increasePosture(
            DEFENDING_POSTURE_RATE
            * deltaTime
        );
    }
    else
    {
        posture =
            std::max(
                0.0f,
                posture
                - POSTURE_RECOVERY_RATE
                * deltaTime
            );
    }

    if (state ==
        CharacterState::GuardBroken)
    {
        guardBreakTimer -= deltaTime;

        if (guardBreakTimer <= 0.0f)
        {
            guardBreakTimer = 0.0f;

            state =
                CharacterState::Idle;
        }
    }

    if (state ==
        CharacterState::Rolling)
    {
        rollTimer -= deltaTime;

        if (rollTimer <= 0.0f)
        {
            rollTimer = 0.0f;

            state =
                CharacterState::Idle;
        }
    }

    if (state ==
        CharacterState::Attacking)
    {
        attackTimer -= deltaTime;

        if (attackTimer <= 0.0f)
        {
            attackTimer = 0.0f;

            state =
                CharacterState::Idle;
        }
    }
}

void Character::move(
    float directionX,
    float directionY,
    float deltaTime,
    float maxX,
    float maxY
)
{
    if (state ==
            CharacterState::Rolling ||
        state ==
            CharacterState::GuardBroken ||
        state ==
            CharacterState::Dead)
    {
        return;
    }

    float length =
        std::sqrt(
            directionX * directionX +
            directionY * directionY
        );

    if (length > 1.0f)
    {
        directionX /= length;
        directionY /= length;
    }

    x += directionX
         * moveSpeed
         * deltaTime;

    y += directionY
         * moveSpeed
         * deltaTime;

    x = std::clamp(
        x,
        0.0f,
        maxX
    );

    y = std::clamp(
        y,
        0.0f,
        maxY
    );
}

int Character::getHP() const
{
    return hp;
}

float Character::getPosture() const
{
    return posture;
}

bool Character::getIsDead() const
{
    return state ==
           CharacterState::Dead;
}

float Character::getX() const
{
    return x;
}

float Character::getY() const
{
    return y;
}

void Character::setPosition(
    float newX,
    float newY
)
{
    x = newX;
    y = newY;
}

CharacterState Character::getState() const
{
    return state;
}

int Character::getAttackPower() const
{
    return attackPower;
}

float Character::getAttackTimer() const
{
    return attackTimer;
}