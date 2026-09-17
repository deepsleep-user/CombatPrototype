#pragma once

class Boss;
class Player;

enum class BossAIState
{
    Idle,
    Chasing,
    Attacking
};

class BossAI
{
private:
    BossAIState state = BossAIState::Idle;

    float aiTimer = 1.0f;

    static constexpr float IDLE_DURATION = 1.0f;
    static constexpr float CHASE_DURATION = 2.0f;
    static constexpr float STOP_DISTANCE = 120.0f;

public:
    void update(
        Boss& boss,
        const Player& player,
        float deltaTime,
        float playerDrawWidth,
        float playerDrawHeight,
        float bossDrawWidth,
        float bossDrawHeight,
        float screenWidth,
        float screenHeight
    );

    BossAIState getState() const;
};