#pragma once

#include "raylib.h"

class GameAssets
{
public:
    // =========================
    // Player Walking Textures
    // =========================

    Texture2D walkRightTexture{};
    Texture2D walkLeftTexture{};
    Texture2D walkUpTexture{};
    Texture2D walkDownTexture{};

    // =========================
    // Player Idle Textures
    // =========================

    Texture2D idleUpTexture{};
    Texture2D idleDownTexture{};
    Texture2D idleLeftTexture{};
    Texture2D idleRightTexture{};

    // =========================
    // Player Attack Textures
    // =========================

    Texture2D attackRightTexture{};
    Texture2D attackLeftTexture{};
    Texture2D attackUpTexture{};
    Texture2D attackDownTexture{};

    // =========================
    // Boss Textures
    // =========================

    Texture2D bossIdleTexture{};
    Texture2D bossWalkTexture{};
    Texture2D bossAttackTexture{};


    // =========================
    // Resource Management
    // =========================

    void load();
    void unload();
};