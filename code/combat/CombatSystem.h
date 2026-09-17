#pragma once

#include "raylib.h"
#include "../physics/FacingDirection.h"

// 前向声明
class Player;
class Boss;

class CombatSystem
{
private:
    // =========================
    // Attack Hitboxes
    // =========================

    Rectangle playerAttackBox{};
    Rectangle bossAttackBox{};


    // =========================
    // Attack Active States
    // =========================

    bool playerAttackActive = false;
    bool bossAttackActive = false;


    // =========================
    // Hit Records
    // =========================

    bool playerAttackHasHit = false;
    bool bossAttackHasHit = false;


public:
    // =========================
    // Update Combat
    // =========================

    void update(
        Player& player,
        Boss& boss,
        Rectangle playerCollision,
        Rectangle bossCollision,
        int playerCurrentFrame,
        float playerDrawWidth,
        float playerDrawHeight,
        FacingDirection playerFacing
    );


    // =========================
    // Reset Attack
    // =========================

    void resetPlayerAttack();
    void resetBossAttack();


    // =========================
    // Debug Draw
    // =========================

    void drawDebug() const;
};