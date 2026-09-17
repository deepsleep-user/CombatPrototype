#include "CollisionSystem.h"

#include "../character/Player.h"
#include "../character/Boss.h"

#include <algorithm>

Rectangle CollisionSystem::createPlayerCollisionBox(
    const Player& player,
    float drawWidth,
    float drawHeight
)
{
    float collisionWidth =
        drawWidth * 0.45f;

    float collisionHeight =
        drawHeight * 0.45f;

    Rectangle collisionBox{
        player.getX()
            + (drawWidth - collisionWidth)
            / 2.0f,

        player.getY()
            + drawHeight
            - collisionHeight,

        collisionWidth,
        collisionHeight
    };

    return collisionBox;
}

Rectangle CollisionSystem::createBossCollisionBox(
    const Boss& boss,
    float drawWidth,
    float drawHeight
)
{   
    float collisionWidth =
        drawWidth * 0.45f;

    float collisionHeight =
        drawHeight * 0.55f;

    Rectangle collisionBox{
        boss.getX()
            + (drawWidth - collisionWidth)
            / 2.0f,

        boss.getY()
            + drawHeight
            - collisionHeight,

        collisionWidth,
        collisionHeight
    };

    return collisionBox;
}

void CollisionSystem::resolveCharacterCollision(
    Player& player,
    const Rectangle& playerCollision,
    const Rectangle& bossCollision
)
{
    if (CheckCollisionRecs(
            playerCollision,
            bossCollision))
    {
        float playerRight =
            playerCollision.x
            + playerCollision.width;

        float playerBottom =
            playerCollision.y
            + playerCollision.height;

        float bossRight =
            bossCollision.x
            + bossCollision.width;

        float bossBottom =
            bossCollision.y
            + bossCollision.height;


        float overlapLeft =
            playerRight
            - bossCollision.x;

        float overlapRight =
            bossRight
            - playerCollision.x;

        float overlapTop =
            playerBottom
            - bossCollision.y;

        float overlapBottom =
            bossBottom
            - playerCollision.y;


        float minOverlapX =
            std::min(
                overlapLeft,
                overlapRight
            );

        float minOverlapY =
            std::min(
                overlapTop,
                overlapBottom
            );


        float playerCenterX =
            playerCollision.x
            + playerCollision.width
                / 2.0f;

        float playerCenterY =
            playerCollision.y
            + playerCollision.height
                / 2.0f;

        float bossCenterX =
            bossCollision.x
            + bossCollision.width
                / 2.0f;

        float bossCenterY =
            bossCollision.y
            + bossCollision.height
                / 2.0f;


        // Resolve collision along the axis
        // with less overlap.
        if (minOverlapX < minOverlapY)
        {
            if (playerCenterX < bossCenterX)
            {
                player.setPosition(
                    player.getX()
                        - overlapLeft,

                    player.getY()
                );
            }
            else
            {
                player.setPosition(
                    player.getX()
                        + overlapRight,

                    player.getY()
                );
            }
        }
        else
        {
            if (playerCenterY < bossCenterY)
            {
                player.setPosition(
                    player.getX(),

                    player.getY()
                        - overlapTop
                );
            }
            else
            {
                player.setPosition(
                    player.getX(),

                    player.getY()
                        + overlapBottom
                );
            }
        }
    }
}