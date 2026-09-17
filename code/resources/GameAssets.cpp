#include "GameAssets.h"

// =========================
// Load Resources
// =========================

void GameAssets::load()
{
    
    walkRightTexture =
        LoadTexture(
            "assets/player/Walking_Right.png"
        );

    walkLeftTexture =
        LoadTexture(
            "assets/player/Walking_Left.png"
        );

    walkUpTexture =
        LoadTexture(
            "assets/player/IdleUpWalking.png"
        );

    walkDownTexture =
        LoadTexture(
            "assets/player/IdleDownWalking.png"
        );

    idleUpTexture =
        LoadTexture(
            "assets/player/IdleUp.png"
        );

    idleDownTexture =
        LoadTexture(
            "assets/player/IdleDown.png"
        );

    idleLeftTexture =
        LoadTexture(
            "assets/player/IdleLeft.png"
        );

    idleRightTexture =
        LoadTexture(
            "assets/player/Idle.png"
        );

    attackRightTexture =
        LoadTexture(
            "assets/player/attack01.png"
        );

    attackLeftTexture =
        LoadTexture(
            "assets/player/attack_left.png"
        );

    attackUpTexture =
        LoadTexture(
            "assets/player/attack01Up.png"
        );

    attackDownTexture =
        LoadTexture(
            "assets/player/attack01Down.png"
        );

    bossIdleTexture =
        LoadTexture(
            "assets/boss/boss_idle.png"
        );

    bossWalkTexture =
        LoadTexture(
            "assets/boss/boss_walk.png"
        );

    bossAttackTexture =
        LoadTexture(
            "assets/boss/boss_attack.png"
        );
}


// =========================
// Unload Resources
// =========================

void GameAssets::unload()
{
    // Player Walking
    UnloadTexture(walkRightTexture);
    UnloadTexture(walkLeftTexture);
    UnloadTexture(walkUpTexture);
    UnloadTexture(walkDownTexture);

    // Player Idle
    UnloadTexture(idleUpTexture);
    UnloadTexture(idleDownTexture);
    UnloadTexture(idleLeftTexture);
    UnloadTexture(idleRightTexture);

    // Player Attack
    UnloadTexture(attackRightTexture);
    UnloadTexture(attackLeftTexture);
    UnloadTexture(attackUpTexture);
    UnloadTexture(attackDownTexture);

    // Boss
    UnloadTexture(bossIdleTexture);
    UnloadTexture(bossWalkTexture);
    UnloadTexture(bossAttackTexture);
}