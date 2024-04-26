#include "PlayerDeadState.h"
#include <GameObject.h>

#include "../../Enum/State/PlayerState.h"

void PlayerDeadState::OnEnter()
{
    GameObject()->SendMsg(PlayerState::Dead, nullptr);
}
