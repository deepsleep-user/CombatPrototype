#include "BossAI.h"

#include "../character/Boss.h"
#include "../character/Player.h"

#include <cmath>

void BossAI::update(
    Boss& boss,
    const Player& player,
    float deltaTime,
    float playerDrawWidth,
    float playerDrawHeight,
    float bossDrawWidth,
    float bossDrawHeight,
    float screenWidth,
    float screenHeight
)
{
    float playerCenterX =
        player.getX()
        + playerDrawWidth / 2.0f;

    float playerCenterY =
        player.getY()
        + playerDrawHeight / 2.0f;

    float bossCenterX =
        boss.getX()
        + bossDrawWidth / 2.0f;

    float bossCenterY =
        boss.getY()
        + bossDrawHeight / 2.0f;

    float directionX =
        playerCenterX - bossCenterX;

    float directionY =
        playerCenterY - bossCenterY;

    float distance =
        std::sqrt(
            directionX * directionX
            +
            directionY * directionY
        );

    switch (state)
    {
        case BossAIState::Idle:
        {
            aiTimer -= deltaTime;

            if (aiTimer <= 0.0f)
            {
                state =
                    BossAIState::Chasing;

                aiTimer =
                    CHASE_DURATION;
            }

            break;
        }

        case BossAIState::Chasing:
        {
            if (distance <= STOP_DISTANCE)
            {
                boss.attack();

                state =
                    BossAIState::Attacking;
            }
            else
            {
                boss.move(
                    directionX,
                    directionY,
                    deltaTime,
                    screenWidth
                        - bossDrawWidth,
                    screenHeight
                        - bossDrawHeight
                );

                aiTimer -= deltaTime;

                if (aiTimer <= 0.0f)
                {
                    state =
                        BossAIState::Idle;

                    aiTimer =
                        IDLE_DURATION;
                }
            }

            break;
        }

        case BossAIState::Attacking:
        {
            if (
                boss.getState()
                != CharacterState::Attacking
            )
            {
                state =
                    BossAIState::Idle;

                aiTimer =
                    IDLE_DURATION;
            }

            break;
        }
    }
}

BossAIState BossAI::getState() const
{
    return state;
}