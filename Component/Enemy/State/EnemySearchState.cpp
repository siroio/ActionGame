#include "EnemySearchState.h"
#include <GameObject.h>
#include <Mathf.h>

#include "../../Enum/State/EnemyState.h"
#include "../CharacterSearcher.h"
#include "../../Common/Damageable.h"

EnemySearchState::EnemySearchState(float searchCoolDown) :
    searchCoolDown_{ searchCoolDown }
{}

void EnemySearchState::OnInitialize()
{
    searcher_ = GameObject()->GetComponent<CharacterSearcher>();
}

int EnemySearchState::OnUpdate(float elapsedTime)
{
    // 一定時間ごとに探索をする
    float eT = searchCoolDown_ <= 0.0f ? 0.0f : Mathf::Mod(elapsedTime, searchCoolDown_);
    if ((eT <= 0.0001f) && OnSearch()) // 計算誤差回避
    {
        // プレイヤーを見つけたら追跡ステートへ推移
        return EnemyState::Chase;
    }
    return STATE_MAINTAIN;
}

bool EnemySearchState::OnSearch()
{
    if (searcher_.expired()) return false;
    return searcher_->TargetInView();
}
