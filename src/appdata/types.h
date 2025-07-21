#pragma once

#include "types-helper.h"

class SkillCardManager
{
public:
};

class CostSkillCardManager : public SkillCardManager
{
public:
    UNITY_CLASS_DECL("BlueArchive.dll", "CostSkillCardManager")

    UNITY_FIELD(float, MaxCost, 0x38)
    UNITY_FIELD(float, CurCost, 0x3c)
    UNITY_FIELD(float, FeverChargeScale, 0x40)
    UNITY_FIELD(float, CostPerFrame, 0x44)
    UNITY_FIELD(bool, IsShuffle, 0x48)
    UNITY_FIELD(int64_t, RegenStartDelayFrame, 0x60)
    UNITY_FIELD(bool, IsMainPlayerSkillCard, 0x68)
    UNITY_FIELD(float, RegenCostBefore, 0x6c)
};

class PlayerSkillCardManager : public CostSkillCardManager {
public:
    UNITY_METHOD_FROM("BlueArchive.dll", "PlayerSkillCardManager", void, ProcessSkillCard, PlayerSkillCardManager*)
};

