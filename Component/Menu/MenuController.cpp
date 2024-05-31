#include "MenuController.h"
#include <GameObject.h>
#include <Mathf.h>
#include <Debugger.h>
#include <GLGUI.h>

#include "MenuItem.h"
#include "../Player/PlayerInput.h"
#include "../../Enum/MessageID.h"

using namespace Glib;

MenuController::MenuController(const Glib::WeakPtr<PlayerInput>& input) :
    input_{ input }
{}

void MenuController::Start()
{
    if (menuItems_.empty())
    {
        Debug::Warn("MenuItem is empty");
        return;
    }

    SyncCursorPosition();
}

void MenuController::Update()
{
    const auto& item = menuItems_.at(currentItemIndex_);
    if (input_->Comfirm())
    {
        // 決定イベントの発行
        item->Comfirm();
        GameObject()->SendMsg(MessageID::Comfirm, nullptr);
        GameObject()->SendMsg(MessageID::Comfirm, nullptr, item->GameObject());
    }
    if (input_->Deny())
    {
        // 拒否イベントの発行
        item->Deny();
        GameObject()->SendMsg(MessageID::Deny, nullptr);
        GameObject()->SendMsg(MessageID::Deny, nullptr, item->GameObject());
    }
    if (input_->Up())
    {
        SelectMenuItem(currentItemIndex_ - 1);
    }
    if (input_->Down())
    {
        SelectMenuItem(currentItemIndex_ + 1);
    }
}

void MenuController::AddFrontItem(const WeakPtr<MenuItem>& item)
{
    menuItems_.push_front(item);
}

void MenuController::AddBackItem(const WeakPtr<MenuItem>& item)
{
    menuItems_.push_back(item);
}

void MenuController::SetCursor(const GameObjectPtr& cursor)
{
    cursor_ = cursor->Transform();
}

void MenuController::SetCursorOffset(const Vector3& offset)
{
    cursorOffset_ = offset;
}

void MenuController::SetCycleCursor(bool cycle)
{
    isCycleCursor_ = cycle;
}

void MenuController::SyncCursorPosition()
{
    if (menuItems_.empty() || cursor_.expired()) return;
    const auto& item = menuItems_.at(currentItemIndex_);
    const auto& itemPosition = item->GameObject()->Transform()->Position();
    cursor_->Position(itemPosition + cursorOffset_);
}

void MenuController::SelectMenuItem(int index)
{
    int selected = index;
    // 選択アイテムのインデックスを循環させるかどうか
    if (isCycleCursor_)
    {
        if (index >= static_cast<int>(menuItems_.size()))
        {
            selected = 0;
        }
        else if (index < 0)
        {
            selected = static_cast<int>(menuItems_.size() - 1);
        }
    }

    // インデックスの境界チェック
    if (selected < 0 || selected >= menuItems_.size()) return;

    currentItemIndex_ = selected;
    const auto& item = menuItems_.at(currentItemIndex_);
    item->Selected();

    // カーソルの位置を同期
    SyncCursorPosition();

    // 移動イベント発行
    GameObject()->SendMsg(MessageID::CursorMove, nullptr);
}

void MenuController::OnGUI()
{
    GLGUI::CheckBox("CycleCursor", &isCycleCursor_);
    GLGUI::DragVector3("CursorOffset", &cursorOffset_);
    GLGUI::Text("SelectedItemIndex: %d", currentItemIndex_);
}
