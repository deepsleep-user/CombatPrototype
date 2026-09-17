#pragma once

#include "raylib.h"
#include "../character/Character.h"
#include "../physics/FacingDirection.h"
#include "../ai/BossAI.h"

class Player;

struct PlayerAnimationResult
{
    Texture2D* texture = nullptr;

    Rectangle sourceRect{};

    float drawWidth = 0.0f;
    float drawHeight = 0.0f;

    int currentFrame = 0;
};

struct BossAnimationResult
{
    Texture2D* texture = nullptr;

    Rectangle sourceRect{};

    int currentFrame = 0;
};

struct AnimationData
{
    int currentFrame = 0;
    float timer = 0.0f;
};

class AnimationSystem
{
private:
    AnimationData playerAnimation;
    AnimationData bossAnimation;

    // 用来判断 CharacterState 是否发生变化
    CharacterState previousPlayerState =
        CharacterState::Idle;
    
    BossAIState previousBossState =
        BossAIState::Idle;

    static constexpr float
        NORMAL_FRAME_DURATION = 0.12f;

    static constexpr float
        ATTACK_FRAME_DURATION = 0.10f;

    static constexpr float
        BOSS_WALK_FRAME_DURATION = 0.15f;


public:
    void initializePlayer(
        const Player& player
    );

    PlayerAnimationResult updatePlayer(
        Player& player,
        FacingDirection facing,
        bool isMoving,
        float deltaTime,

        Texture2D& walkRightTexture,
        Texture2D& walkLeftTexture,
        Texture2D& walkUpTexture,
        Texture2D& walkDownTexture,

        Texture2D& idleUpTexture,
        Texture2D& idleDownTexture,
        Texture2D& idleLeftTexture,
        Texture2D& idleRightTexture,

        Texture2D& attackRightTexture,
        Texture2D& attackLeftTexture,
        Texture2D& attackUpTexture,
        Texture2D& attackDownTexture
    );

    BossAnimationResult updateBoss(
    BossAIState bossAIState,
    float deltaTime,

    Texture2D& bossIdleTexture,
    Texture2D& bossWalkTexture,
    Texture2D& bossAttackTexture
    );
};