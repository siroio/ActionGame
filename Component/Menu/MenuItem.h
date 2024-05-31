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
    virtual void Deny() = 0;

    /**
     * @brief 選択時
     */
    virtual void Selected() = 0;
};
