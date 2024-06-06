#pragma once

struct AudioID
{
    enum : unsigned int
    {
        PlayerSwing = 0,
        EnemyDead,

        Field = 10,
        Battle,
        Title,
        GameOver,
        GameClear,

        ButtonPush = 20,
        CursorMove,
    };
};
