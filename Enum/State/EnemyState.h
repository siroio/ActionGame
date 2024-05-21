#pragma once

struct EnemyState
{
    enum
    {
        // 共通ステート

        Selector,
        Search,
        Moving,
        Chase,
        Damage,
        Dead,

        // 近接攻撃
        MeleeAttack,
        MaelstromAttack,

        // 遠距離攻撃
        ProjectileAttack,
    };
};
