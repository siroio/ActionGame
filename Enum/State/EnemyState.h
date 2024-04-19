#pragma once

struct EnemyState
{
    enum
    {
        Search,
        Moving,
        Chase,
        Damage,
        Dead,

        // 近接攻撃
        MeleeAttack,
    };
};
