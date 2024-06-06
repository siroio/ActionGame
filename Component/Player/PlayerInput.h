#pragma once
#include <Component.h>

struct Vector2;

/**
 * @brief プレイヤーの入力クラス
 */
class PlayerInput : public Component
{
public:
    bool Pose() const;
    bool Comfirm() const;
    bool Deny() const;
    bool Up() const;
    bool Down() const;
    bool Attack() const;
    bool Dodge() const;
    Vector2 Camera() const;
    Vector2 Move() const;

    /**
     * @brief 入力の切り替え
     * @param enable
     */
    void InputEnable(bool enable);

private:
    bool enable_{ true };
};
