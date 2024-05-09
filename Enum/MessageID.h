#pragma once

struct MessageID
{
    enum
    {
        Attacked,
        Dead,
        BattleStart,
        BattleClear,
        GameClear,
        GameOver,
    };
};
