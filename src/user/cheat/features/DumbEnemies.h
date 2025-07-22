#pragma once

class DumbEnemies
{
public:
    static void init();

private:
    static bool hCanBeTargeted(BattleEntity* _this, BattleEntity* attacker, SkillSlot_Enum skillSlot);
};
