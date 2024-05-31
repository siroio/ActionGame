#pragma once
#include <Component.h>

/**
 * @brief メニュー表示用アイテムの基底コンポーネント
 */
class MenuItem : public Component
{
public:
    /**
     * @brief 決定
     */
    virtual void Comfirm() = 0;

    /**
     * @brief 拒否
     */
    virtual void Deny()
    {};

    /**
     * @brief 選択時
     */
    virtual void Selected()
    {};
};
