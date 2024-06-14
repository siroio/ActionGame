#pragma once
#include <Component.h>
#include <GameObjectPtr.h>
#include <Vector3.h>
#include <deque>

namespace Glib
{
    class Transform;
}

class MenuItem;
class PlayerInput;

/**
 * @brief メニュー制御コンポーネント
 */
class MenuController : public Component
{
public:
    MenuController(const Glib::WeakPtr<PlayerInput>& input);
    void Start();
    void Update();

    /**
     * @brief 先頭にアイテムを追加
     * @param item 表示アイテム
     */
    void AddFrontItem(const Glib::WeakPtr<MenuItem>& item);

    /**
     * @brief 後方にアイテムを追加
     * @param item 表示アイテム
     */
    void AddBackItem(const Glib::WeakPtr<MenuItem>& item);

    /**
     * @brief カーソルを設定
     * @param cursor
     */
    void SetCursor(const GameObjectPtr& cursor);

    /**
     * @brief カーソルの表示オフセットを設定
     * @param offset
     */
    void SetCursorOffset(const Vector3& offset);

    /**
     * @brief カーソルを循環させるか
     * @param cycle
     */
    void SetCycleCursor(bool cycle);

private:
    void SyncCursorPosition();
    void SelectMenuItem(int index);
    void OnGUI();

private:
    std::deque<Glib::WeakPtr<MenuItem>> menuItems_{};
    Glib::WeakPtr<Glib::Transform> cursor_{};
    Glib::WeakPtr<PlayerInput> input_{};
    unsigned int currentItemIndex_{ 0 };
    Vector3 cursorOffset_{ 0.0f, 0.0f, 0.0f };
    bool isCycleCursor_{ false };
};
