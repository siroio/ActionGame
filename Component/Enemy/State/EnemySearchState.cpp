#include "EnemySearchState.h"
#include <GameObject.h>
#include <Mathf.h>

#include "../../Enum/State/EnemyState.h"
#include "../CharacterSearcher.h"
#include "../../Common/Damageable.h"


EnemySearchState::EnemySearchState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void EnemySearchState::OnInitialize()
{
    searcher_ = GameObject()->GetComponent<CharacterSearcher>();
}

int EnemySearchState::OnUpdate(float elapsedTime)
{
    // 一定時間ごとに探索をする
    if (Mathf::Mod(elapsedTime, parameter_.searchCoolDown))
    {
        // プレイヤーを見つけたら追跡ステートへ推移
        const bool isFound{ OnSearch() };
        return isFound ? EnemyState::Chase : STATE_MAINTAIN;
    }

    return STATE_MAINTAIN;
}

bool EnemySearchState::OnSearch()
{
    if (searcher_.expired()) return false;
    return searcher_->TargetInView();
}
