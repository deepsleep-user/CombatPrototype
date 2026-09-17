#pragma once

enum class CharacterState
{
    Idle,
    Attacking,
    Defending,
    Rolling,
    GuardBroken,
    Dead
};

class Character
{
protected:
    // 基础战斗属性
    int hp;
    float posture;
    int attackPower;
    int defense;

    // 二维位置与移动
    float x;
    float y;
    float moveSpeed;

    // 状态计时器
    float guardBreakTimer = 0.0f;
    float rollTimer = 0.0f;
    float attackTimer = 0.0f;

    // 战斗规则
    static constexpr float MAX_POSTURE = 100.0f;
    static constexpr float POSTURE_RECOVERY_RATE = 15.0f;
    static constexpr float DEFENDING_POSTURE_RATE = 8.0f;
    static constexpr float BLOCK_POSTURE_COST = 20.0f;

    static constexpr float GUARD_BREAK_DURATION = 1.0f;
    static constexpr float ROLL_DURATION = 0.25f;
    static constexpr float ATTACK_DURATION = 0.5f;

    CharacterState state = CharacterState::Idle;

public:
    Character(
        int initialHP,
        float initialPosture,
        int initialAttackPower,
        int initialDefense,
        float initialX,
        float initialY,
        float initialMoveSpeed
    );

    virtual ~Character() = default;

    virtual void showStatus() const;
    void showState() const;

    void takeDamage(int damage);
    void attack();

    void defend();
    void stopDefending();

    void roll();

    void increasePosture(float amount);
    void guardBreak();

    void die();

    void update(float deltaTime);

    void move(
        float directionX,
        float directionY,
        float deltaTime,
        float maxX,
        float maxY
    );

    int getHP() const;
    float getPosture() const;
    bool getIsDead() const;

    float getX() const;
    float getY() const;

    void setPosition(
        float newX,
        float newY
    );

    CharacterState getState() const;

    int getAttackPower() const;

    float getAttackTimer() const;
};