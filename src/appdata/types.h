#pragma once

#include "enums.h"
#include "types-helper.h"

// All forward declarations
class SkillCardManager;
class CostSkillCardManager;
class PlayerSkillCardManager;
class BattleEntity;
class BattleSummary;
class Battle;
class PlayerGroup;

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
    UNITY_FIELD(int64_t, HitPoint, 0x78)
    UNITY_FIELD(int64_t, HitPointBefore, 0x80)
    UNITY_FIELD(int64_t, MaxHPCapGauge, 0x88)
    UNITY_FIELD(int64_t, SummonedTime, 0x90)
    UNITY_FIELD(ArmorType_Enum, ArmorType, 0x98)
    // UNITY_FIELD(BattleEntityStatProcessor*, statProcessor, 0xA0);

    UNITY_METHOD(bool, CanBeTargeted, BattleEntity*, BattleEntity*, SkillSlot_Enum)
    UNITY_METHOD(int64_t, AddHitPoint, BattleEntity*, int64_t)
};

class BattleSummary
{
public:
    UNITY_CLASS_DECL("BlueArchive.dll", "BattleSummary")

    UNITY_FIELD(int64_t, HashKey, 0x10)
    UNITY_FIELD(bool, IsBossBattle, 0x18)
    UNITY_FIELD(BattleTypes_Enum, BattleType, 0x1C)
    UNITY_FIELD(int64_t, StageId, 0x20)
    UNITY_FIELD(int64_t, GroundId, 0x28)
    UNITY_FIELD(GroupTag_Enum, Winner, 0x30)
    UNITY_FIELD(BattleEndType_Enum, EndType, 0x34)
    UNITY_FIELD(int, EndFrame, 0x38)
    UNITY_FIELD(double, UnitType, 0x40)
    UNITY_FIELD(double, ResultValue, 0x48)
    UNITY_FIELD(int, ContinueCount, 0x78)
    UNITY_FIELD(float, ElapsedRealtime, 0x7C)
    UNITY_FIELD(int, writeFrame, 0x80)
    UNITY_FIELD(int64_t, EventContentId, 0x88)
    UNITY_FIELD(int64_t, FixedEchelonId, 0x90)
    UNITY_FIELD(bool, IsAbort, 0x98)
    UNITY_FIELD(bool, IsDefeatBattle, 0x99)
    UNITY_FIELD(Battle*, battle, 0xA0)

    UNITY_METHOD(void, InitBattleTypeSummary, BattleSummary*, Battle*)
    UNITY_METHOD(void, Finalize, BattleSummary*, Battle*, GroupTag_Enum, BattleEndType_Enum, int, float)
};

class Battle
{
public:
    UNITY_CLASS_DECL("BlueArchive.dll", "Battle")

    UNITY_FIELD(BattleLogicState_Enum, state, 0x188)
    UNITY_FIELD(int64_t, StartTickRealTime, 0x198)
    UNITY_FIELD(int, MaxDurationFrame, 0x1A0)
    // UNITY_FIELD(UnityResolve::UnityType::List<>, AllActiveCharacters, 0x1B0)
    // UNITY_FIELD(UnityResolve::UnityType::List<>, AllAliveCharacters, 0x1B8)
    // UNITY_FIELD(O139cb8484a6efbeade5b8c6d40e89e4aec30556aa791f82dc4247b81d8d0d42d, LogicEffectProcessor, 0x1D8)
    UNITY_FIELD(BattleSummary*, BattleSummary_, 0x1F0)
    UNITY_FIELD(double, UnitType, 0x200)
    UNITY_FIELD(double, ResultValue, 0x208)
    UNITY_FIELD(PlayerGroup*, playerGroup, 0x220)
    UNITY_FIELD(int, TotalEnemyCount, 0x2F8)
    UNITY_FIELD(int, RemainEnemyCount, 0x2FC)
    

    UNITY_METHOD(void, Update, Battle*)
};

class PlayerGroup
{
public:
    UNITY_FIELD(int, EchelonNumber, 0x140)
    UNITY_FIELD(PlayerSkillCardManager*, PlayerSkillCardManager_, 0x150)
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
