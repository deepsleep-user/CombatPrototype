#include "CombatSystem.h"
#include "../character/Player.h"
#include "../character/Boss.h"


// =========================
// Update Combat
// =========================

void CombatSystem::update(
    Player& player,
    Boss& boss,
    Rectangle playerCollision,
    Rectangle bossCollision,
    int playerCurrentFrame,
    float playerDrawWidth,
    float playerDrawHeight,
    FacingDirection playerFacing
)
{
    // =========================
    // 1. Player Attack Active
    // =========================

    // Player 的攻击动画第 2、3 帧
    // 才具有攻击判定
    playerAttackActive =
        player.getState() ==
            CharacterState::Attacking &&
        (
            playerCurrentFrame == 2 ||
            playerCurrentFrame == 3
        );


    // =========================
    // 2. Player Attack Hitbox
    // =========================

   if (playerAttackActive)
   {
        switch (playerFacing)
        {
            case FacingDirection::Right:
            {
                playerAttackBox =
                {
                    player.getX() + playerDrawWidth,
                    player.getY(),
                    80.0f,
                    playerDrawHeight
                };

                break;
            }

            case FacingDirection::Left:
            {
                playerAttackBox =
                {
                    player.getX() - 80.0f,
                    player.getY(),
                    80.0f,
                    playerDrawHeight
                };

                break;
            }

            case FacingDirection::Up:
            {
                playerAttackBox =
                {
                    player.getX(),
                    player.getY() - 80.0f,
                    playerDrawWidth,
                    80.0f
                };

                break;
            }

            case FacingDirection::Down:
            {
                playerAttackBox =
                {
                    player.getX(),
                    player.getY() + playerDrawHeight,
                    playerDrawWidth,
                    80.0f
                };

                break;
            }
        }
    }

    // =========================
    // 3. Boss Attack Active
    // =========================

    float bossAttackTimer =
        boss.getAttackTimer();

    bossAttackActive =
        boss.getState() ==
            CharacterState::Attacking &&
        bossAttackTimer <= 0.35f &&
        bossAttackTimer >= 0.15f;


    // =========================
    // 4. Boss Attack Hitbox
    // =========================

    if (bossAttackActive)
    {
        bossAttackBox =
        {
            bossCollision.x - 40.0f,
            bossCollision.y - 40.0f,

            bossCollision.width + 80.0f,
            bossCollision.height + 80.0f
        };
    }


    // =========================
    // 5. Player Attacks Boss
    // =========================

    if (
        playerAttackActive &&
        !playerAttackHasHit &&
        CheckCollisionRecs(
            playerAttackBox,
            bossCollision
        )
    )
    {
        boss.takeDamage(
            player.getAttackPower()
        );

        playerAttackHasHit = true;
    }


    // =========================
    // 6. Boss Attacks Player
    // =========================

    if (
        bossAttackActive &&
        !bossAttackHasHit &&
        CheckCollisionRecs(
            bossAttackBox,
            playerCollision
        )
    )
    {
        player.takeDamage(
            boss.getAttackPower()
        );

        bossAttackHasHit = true;
    }
}


// =========================
// Reset Player Attack
// =========================

void CombatSystem::resetPlayerAttack()
{
    playerAttackHasHit = false;
}


// =========================
// Reset Boss Attack
// =========================

void CombatSystem::resetBossAttack()
{
    bossAttackHasHit = false;
}


// =========================
// Draw Debug Hitboxes
// =========================

void CombatSystem::drawDebug() const
{
    if (playerAttackActive)
    {
        DrawRectangleLinesEx(
            playerAttackBox,
            2.0f,
            BLUE
        );
    }

    if (bossAttackActive)
    {
        DrawRectangleLinesEx(
            bossAttackBox,
            2.0f,
            ORANGE
        );
    }
}