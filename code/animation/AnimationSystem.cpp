#include "AnimationSystem.h"
#include "../character/Player.h"

void AnimationSystem::initializePlayer(
    const Player& player
)
{
    previousPlayerState =
        player.getState();

    playerAnimation.currentFrame = 0;
    playerAnimation.timer = 0.0f;
}
PlayerAnimationResult AnimationSystem::updatePlayer(
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
)
{
    PlayerAnimationResult result;

    CharacterState currentState =
        player.getState();


    // =========================
    // 1. State Change
    // =========================

    if (currentState != previousPlayerState)
    {
        playerAnimation.currentFrame = 0;
        playerAnimation.timer = 0.0f;

        previousPlayerState =
            currentState;
    }


    // =========================
    // 2. Choose Animation
    // =========================

    Texture2D* currentTexture =
        nullptr;

    int currentFrameCount = 0;

    float currentFrameDuration =
        NORMAL_FRAME_DURATION;


    if (
        currentState ==
        CharacterState::Attacking
    )
    {
        currentFrameDuration =
            ATTACK_FRAME_DURATION;

        switch (facing)
        {
            case FacingDirection::Up:
                currentTexture =
                    &attackUpTexture;
                currentFrameCount = 5;
                break;

            case FacingDirection::Down:
                currentTexture =
                    &attackDownTexture;
                currentFrameCount = 5;
                break;

            case FacingDirection::Left:
                currentTexture =
                    &attackLeftTexture;
                currentFrameCount = 5;
                break;

            case FacingDirection::Right:
                currentTexture =
                    &attackRightTexture;
                currentFrameCount = 5;
                break;
        }
    }

    else if (isMoving)
    {
        switch (facing)
        {
            case FacingDirection::Up:
                currentTexture =
                    &walkUpTexture;
                currentFrameCount = 4;
                break;

            case FacingDirection::Down:
                currentTexture =
                    &walkDownTexture;
                currentFrameCount = 4;
                break;

            case FacingDirection::Left:
                currentTexture =
                    &walkRightTexture;
                currentFrameCount = 4;
                break;

            case FacingDirection::Right:
                currentTexture =
                    &walkLeftTexture;
                currentFrameCount = 4;
                break;
        }
    }

    else
    {
        switch (facing)
        {
            case FacingDirection::Up:
                currentTexture =
                    &idleUpTexture;
                currentFrameCount = 2;
                break;

            case FacingDirection::Down:
                currentTexture =
                    &idleDownTexture;
                currentFrameCount = 2;
                break;

            case FacingDirection::Left:
                currentTexture =
                    &idleLeftTexture;
                currentFrameCount = 8;
                break;

            case FacingDirection::Right:
                currentTexture =
                    &idleRightTexture;
                currentFrameCount = 8;
                break;
        }
    }


    // =========================
    // 3. Texture Frame Size
    // =========================

    float frameWidth =
        static_cast<float>(
            currentTexture->width
        ) / currentFrameCount;

    float frameHeight =
        static_cast<float>(
            currentTexture->height
        );


    // =========================
    // 4. Protect Frame Range
    // =========================

    if (
        playerAnimation.currentFrame >=
        currentFrameCount
    )
    {
        playerAnimation.currentFrame = 0;
    }


    // =========================
    // 5. Update Animation Timer
    // =========================

    playerAnimation.timer +=
        deltaTime;

    if (
        playerAnimation.timer >=
        currentFrameDuration
    )
    {
        playerAnimation.timer = 0.0f;

        playerAnimation.currentFrame++;

        if (
            playerAnimation.currentFrame >=
            currentFrameCount
        )
        {
            playerAnimation.currentFrame = 0;
        }
    }


    // =========================
    // 6. Source Rectangle
    // =========================

    result.sourceRect =
    {
        playerAnimation.currentFrame * frameWidth,
        0.0f,
        frameWidth,
        frameHeight
    };


    // =========================
    // 7. Draw Size
    // =========================

    result.drawWidth =
        frameWidth * 2.0f;

    result.drawHeight =
        frameHeight * 2.0f;


    // =========================
    // 8. Output
    // =========================

    result.texture =
        currentTexture;

    result.currentFrame =
        playerAnimation.currentFrame;

    return result;
}

BossAnimationResult AnimationSystem::updateBoss(
    BossAIState bossAIState,
    float deltaTime,

    Texture2D& bossIdleTexture,
    Texture2D& bossWalkTexture,
    Texture2D& bossAttackTexture
)
{
    BossAnimationResult result;

    Texture2D* currentBossTexture =
        nullptr;

    int bossFrameCount = 1;

    // =========================
    // 1. Boss State Change
    // =========================

    if (
        bossAIState !=
        previousBossState
    )
    {
        bossAnimation.currentFrame = 0;
        bossAnimation.timer = 0.0f;

        previousBossState =
            bossAIState;
    }


    // =========================
    // 2. Choose Boss Animation
    // =========================

    switch (bossAIState)
    {
        case BossAIState::Idle:
        {
            currentBossTexture =
                &bossIdleTexture;

            bossFrameCount = 1;

            break;
        }

        case BossAIState::Chasing:
        {
            currentBossTexture =
                &bossWalkTexture;

            bossFrameCount = 4;

            break;
        }

        case BossAIState::Attacking:
        {
            currentBossTexture =
                &bossAttackTexture;

            bossFrameCount = 1;

            break;
        }
    }
    // =========================
    // 3. Boss Frame Size
    // =========================

    float currentBossFrameWidth =
        static_cast<float>(
            currentBossTexture->width
        ) / bossFrameCount;

    float currentBossFrameHeight =
        static_cast<float>(
            currentBossTexture->height
        );


    // =========================
    // 4. Protect Frame Range
    // =========================

    if (
        bossAnimation.currentFrame >=
        bossFrameCount
    )
    {
        bossAnimation.currentFrame = 0;
    }

    // =========================
    // 5. Update Boss Animation
    // =========================

    if (
        bossAIState ==
        BossAIState::Chasing
    )
    {
        bossAnimation.timer +=
            deltaTime;

        if (
            bossAnimation.timer >=
            BOSS_WALK_FRAME_DURATION
        )
        {
            bossAnimation.timer = 0.0f;

            bossAnimation.currentFrame++;

            if (
                bossAnimation.currentFrame >=
                bossFrameCount
            )
            {
                bossAnimation.currentFrame = 0;
            }
        }
    }
    else
    {
        bossAnimation.currentFrame = 0;
    }

    // =========================
    // 6. Boss Source Rectangle
    // =========================

    result.sourceRect =
    {
        bossAnimation.currentFrame
            * currentBossFrameWidth,

        0.0f,

        currentBossFrameWidth,
        currentBossFrameHeight
    };


    // =========================
    // 7. Output
    // =========================

    result.texture =
        currentBossTexture;

    result.currentFrame =
        bossAnimation.currentFrame;

    return result;
}