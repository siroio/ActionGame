﻿#pragma once

struct AnimationID
{
    enum : unsigned int
    {
        PlayerIdle = 0,
        PlayerMove,
        PlayerRolling,
        PlayerDamage,
        PlayerDeath,
        PlayerAttack1,
        PlayerAttack2,
        PlayerAttack3,
        PlayerAttack4,
        PlayerUpArm,

        SkeletonAttack = 10,
        SkeletonDeath,
        SkeletonDamage,
        SkeletonMove,
        SkeletonIdle,

        MageAttack = 20,
        MageDeath,
        MageDamage,
        MageMove,
        MageIdle,

        GolemAttack1 = 30,
        GolemAttack2,
        GolemDamage,
        GolemMove,
        GolemIdle,
    };
};
