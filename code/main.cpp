#include "raylib.h"

#include "character/Player.h"
#include "character/Boss.h"
#include "combat/CombatSystem.h"
#include "ai/BossAI.h"
#include "physics/FacingDirection.h"
#include "animation/AnimationSystem.h"
#include "resources/GameAssets.h"
#include "physics/CollisionSystem.h"

#include <cmath>

int main()
{
    // =========================
    // Window
    // =========================

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(
        screenWidth,
        screenHeight,
        "Combat Prototype"
    );

    SetTargetFPS(60);

    // =========================
    // Characters
    // =========================

    Player wolf(
        100,        // HP
        0.0f,       // Posture
        30,         // Attack Power
        10,         // Defense
        100.0f,     // X
        100.0f,     // Y
        200.0f      // Move Speed
    );

    Boss genichiro(
        200,        // HP
        0.0f,       // Posture
        40,         // Attack Power
        15,         // Defense
        500.0f,     // X
        300.0f,     // Y
        100.0f      // Move Speed
    );

    // =========================
    // Game Assets
    // =========================

    GameAssets assets;

    assets.load();

    // =========================
    // Player Facing Direction
    // =========================

    FacingDirection facing =
        FacingDirection::Down;

    // =========================
    // Game System
    // =========================

    BossAI bossAI;
    CombatSystem combatSystem;

    CollisionSystem collisionSystem;

    AnimationSystem animationSystem;
    animationSystem.initializePlayer(wolf);

    // =========================
    // Previous State Records
    // =========================

    CharacterState previousCombatState =
        wolf.getState();

    BossAIState previousBossAIState =
        bossAI.getState();

    // =========================
    // Game Loop
    // =========================

    while (!WindowShouldClose())
    {
        // =========================
        // Time
        // =========================

        float deltaTime =
            GetFrameTime();

        // =========================
        // Player Input
        // =========================

        float directionX = 0.0f;
        float directionY = 0.0f;

        if (IsKeyDown(KEY_W))
        {
            directionY -= 1.0f;
            facing =
                FacingDirection::Up;
        }

        if (IsKeyDown(KEY_S))
        {
            directionY += 1.0f;
            facing =
                FacingDirection::Down;
        }

        if (IsKeyDown(KEY_A))
        {
            directionX -= 1.0f;
            facing =
                FacingDirection::Left;
        }

        if (IsKeyDown(KEY_D))
        {
            directionX += 1.0f;
            facing =
                FacingDirection::Right;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            wolf.attack();
        }

        bool isMoving =
            directionX != 0.0f ||
            directionY != 0.0f;

        // =========================
        // Character State Update
        // =========================

        wolf.update(deltaTime);
        genichiro.update(deltaTime);

        CharacterState currentCombatState =
            wolf.getState();

        if (
            currentCombatState !=
            previousCombatState &&
            currentCombatState ==
                CharacterState::Attacking
            )
        {
            combatSystem.resetPlayerAttack();
        }

        previousCombatState =
            currentCombatState;

        // =========================
        // Player Animation
        // =========================

        PlayerAnimationResult playerAnimation =
            animationSystem.updatePlayer(
            wolf,
            facing,
            isMoving,
            deltaTime,

            assets.walkRightTexture,
            assets.walkLeftTexture,
            assets.walkUpTexture,
            assets.walkDownTexture,

            assets.idleUpTexture,
            assets.idleDownTexture,
            assets.idleLeftTexture,
            assets.idleRightTexture,

            assets.attackRightTexture,
            assets.attackLeftTexture,
            assets.attackUpTexture,
            assets.attackDownTexture
        );

        Texture2D* currentTexture =
            playerAnimation.texture;

        Rectangle sourceRect =
            playerAnimation.sourceRect;

        float drawWidth =
            playerAnimation.drawWidth;

        float drawHeight =
            playerAnimation.drawHeight;

        int currentFrame =
            playerAnimation.currentFrame;

    
        
        // =========================
        // Boss Draw Size
        // =========================

        float bossFrameWidth =
            static_cast<float>(
                assets.bossIdleTexture.width
            );

        float bossFrameHeight =
            static_cast<float>(
                assets.bossIdleTexture.height
            );

        float bossDrawWidth =
            bossFrameWidth * 7.0f;

        float bossDrawHeight =
            bossFrameHeight * 7.0f;

        // =========================
        // Player Movement
        // =========================

        wolf.move(
            directionX,
            directionY,
            deltaTime,
            static_cast<float>(
                screenWidth
            ) - drawWidth,
            static_cast<float>(
                screenHeight
            ) - drawHeight
        );

        // =========================
        // Boss AI and Animation
        // =========================

        bossAI.update(
            genichiro,
            wolf,
            deltaTime,
            drawWidth,
            drawHeight,
            bossDrawWidth,
            bossDrawHeight,
            static_cast<float>(screenWidth),
            static_cast<float>(screenHeight)
            );

        BossAIState bossAIState = bossAI.getState();

        BossAnimationResult bossAnimationResult =
            animationSystem.updateBoss(
            bossAIState,
            deltaTime,

            assets.bossIdleTexture,
            assets.bossWalkTexture,
            assets.bossAttackTexture
        );

        // =========================
        // Boss Attack State Change
        // =========================

        if (bossAIState !=
            previousBossAIState) // Reset hit record when a new boss attack starts.
        {
            if (bossAIState == BossAIState::Attacking)
            {
                combatSystem.resetBossAttack();
            }

            previousBossAIState = bossAIState;
        }
        
        // =========================
        // Character Collision Boxes
        // =========================

        Rectangle playerCollision =
            collisionSystem.createPlayerCollisionBox(
            wolf,
            drawWidth,
            drawHeight
        );

        Rectangle bossCollision =
            collisionSystem.createBossCollisionBox(
            genichiro,
            bossDrawWidth,
            bossDrawHeight
        );

        // =========================
        // Combat System
        // =========================

        combatSystem.update(
            wolf,
            genichiro,
            playerCollision,
            bossCollision,
            currentFrame,
            drawWidth,
            drawHeight,
            facing
        );

        // =========================
        // Character Collision Resolution
        // =========================

        collisionSystem.resolveCharacterCollision(
            wolf,
            playerCollision,
            bossCollision
        );

        playerCollision =
            collisionSystem.createPlayerCollisionBox(
            wolf,
            drawWidth,
            drawHeight
        );

        // =========================
        // Destination Rectangles
        // =========================

        Rectangle playerDestRect{
            wolf.getX(),
            wolf.getY(),
            drawWidth,
            drawHeight
        };

        Rectangle bossDestRect{
            genichiro.getX(),
            genichiro.getY(),
            bossDrawWidth,
            bossDrawHeight
        };

        // =========================
        // Rendering
        // =========================

        BeginDrawing();

        ClearBackground(
            RAYWHITE
        );

        // -------------------------
        // Player
        // -------------------------

        DrawTexturePro(
            *currentTexture,
            sourceRect,
            playerDestRect,
            Vector2{
                0.0f,
                0.0f
            },
            0.0f,
            WHITE
        );

        // -------------------------
        // Boss
        // -------------------------

        DrawTexturePro(
            *bossAnimationResult.texture,
            bossAnimationResult.sourceRect,
            bossDestRect,
            Vector2{
                0.0f,
                0.0f
            },
            0.0f,
            WHITE
        );

        // -------------------------
        // Collision Debug
        // -------------------------

        DrawRectangleLinesEx(
            playerCollision,
            2.0f,
            GREEN
        );

        DrawRectangleLinesEx(
            bossCollision,
            2.0f,
            RED
        );

       combatSystem.drawDebug();

        // -------------------------
        // HP UI
        // -------------------------

        DrawText(
            TextFormat(
                "Player HP: %d",
                wolf.getHP()
            ),
            20,
            20,
            20,
            BLACK
        );

        DrawText(
            TextFormat(
                "Boss HP: %d",
                genichiro.getHP()
            ),
            20,
            50,
            20,
            BLACK
        );

        // -------------------------
        // Death Messages
        // -------------------------

        if (wolf.getIsDead())
        {
            DrawText(
                "YOU DIED",
                300,
                250,
                40,
                RED
            );
        }

        if (genichiro.getIsDead())
        {
            DrawText(
                "BOSS DEFEATED",
                250,
                250,
                40,
                DARKGREEN
            );
        }

        EndDrawing();
    }

    // =========================
    // Release Resources
    // =========================

    assets.unload();

    CloseWindow();

    return 0;
}