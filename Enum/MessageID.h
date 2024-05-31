#pragma once

struct MessageID
{
    enum
    {
        Attacked,
        Dead,
        BattleStart,
        BattleClear,
        WaveClear,
        GameClear,
        GameOver,
        Comfirm,
        Deny,
        CursorMove,
    };
};
