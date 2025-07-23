#pragma once

#include "enums.h"
#include "types-helper.h"

class SkillCardManager
{
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

class PlayerSkillCardManager : public CostSkillCardManager
{
public:
    UNITY_METHOD_FROM("BlueArchive.dll", "PlayerSkillCardManager", void, ProcessSkillCard, PlayerSkillCardManager*)
};

class BattleEntity
{
public:
    UNITY_CLASS_DECL("BlueArchive.dll", "BattleEntity")

    UNITY_FIELD(TacticEntityType_Enum, TacticEntityType, 0x38)
    UNITY_FIELD(UnityResolve::UnityType::String*, Name, 0x58)
    // UNITY_FIELD(Body2D*, Body, 0x60);
    UNITY_FIELD(int64_t, HitPoint, 0x78)
    UNITY_FIELD(int64_t, HitPointBefore, 0x80)
    UNITY_FIELD(int64_t, MaxHPCapGauge, 0x88)
    UNITY_FIELD(int64_t, SummonedTime, 0x90)
    // UNITY_FIELD(BattleEntityStatProcessor*, statProcessor, 0xA0);

    UNITY_METHOD(bool, CanBeTargeted, BattleEntity*, BattleEntity*, SkillSlot_Enum)
};

class Battle
{
public:
    UNITY_CLASS_DECL("BlueArchive.dll", "Battle")

    UNITY_METHOD(void, Update, Battle*)
};

// struct DamageByHitEffect__Fields {
//     struct LogicEffect__Fields _;
//     struct DamageByHitEffectValue *_value_k__BackingField;
//     struct BasisPoint _DamageMultiplier_k__BackingField;
//     struct IList_1_MX_Logic_Data_AbilityModifier_ *_DamageModifiers_k__BackingField;
//     struct Battle *battle;
//     struct Odf22856f604e4831468153c7b168db244fdfe41f97511ace15c9f569879dc5d4 *logicEffectProcessor;
//     struct ExpirableObjectHolder_1_DotAbility_ *ability;
//     struct ExtraStatDamageEffectValue *extraStatDamageEffectValue;
//     int32_t CurrentCount;
// };
