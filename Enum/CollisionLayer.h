#pragma once

struct CollisionLayer
{
    enum : unsigned int
    {
        Default,            // デフォルト
        Stage,              // ステージ
        Player,             // プレイヤー
        PlayerAttack,       // プレイヤー攻撃
        Enemy,              // 敵
        EnemyAttack,        // 敵攻撃
        BattleArea,         // 戦闘エリア
    };
};
