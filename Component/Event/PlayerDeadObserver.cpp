#include "PlayerDeadObserver.h"
#include <GameObject.h>
#include <GameObjectManager.h>

#include "../Common/Damageable.h"
#include "../../Enum/MessageID.h"
#include "../../Constant/GameObjectName.h"

using namespace Glib;

void PlayerDeadObserver::Start()
{
    auto player = GameObjectManager::Find(ObjectName::Player);

    if (player.expired())
    {
        Destroy();
    }

    damageable_ = player->GetComponent<Damageable>();
}

void PlayerDeadObserver::Update()
{
    // 死亡しているか監視
    if (!damageable_->IsDead()) return;
    GameObject()->SendMsg(MessageID::Dead, nullptr);

    // 一度だけ送りたいので
    // コンポーネントを無効に設定
    Active(false);
}
