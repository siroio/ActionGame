#pragma once

struct AnimationID
{
    enum : unsigned int
    {
        PlayerIdle,
        PlayerMove,
        PlayerRolling,
        PlayerDamage,
        PlayerDeath,
        PlayerAttack1,
        PlayerAttack2,
        PlayerAttack3,
        PlayerAttack4,

        SkeletonAttack = 9,
        SkeletonDeath,
        SkeletonDamage,
        SkeletonMove,
        SkeletonIdle,
    };
};
