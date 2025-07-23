#pragma once

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

enum class TacticEntityType_Enum : int32_t
{
    None = 0x00000000,
    Student = 0x00000001,
    Minion = 0x00000002,
    Elite = 0x00000004,
    Champion = 0x00000008,
    Boss = 0x00000010,
    Obstacle = 0x00000020,
    Servant = 0x00000040,
    Vehicle = 0x00000080,
    Summoned = 0x00000100,
    Hallucination = 0x00000200,
    DestructibleProjectile = 0x00000400,
};

enum class SkillSlot_Enum : int32_t
{
    None = 0x00000000,
    NormalAttack01 = 0x00000001,
    NormalAttack02 = 0x00000002,
    NormalAttack03 = 0x00000003,
    NormalAttack04 = 0x00000004,
    NormalAttack05 = 0x00000005,
    NormalAttack06 = 0x00000006,
    NormalAttack07 = 0x00000007,
    NormalAttack08 = 0x00000008,
    NormalAttack09 = 0x00000009,
    NormalAttack10 = 0x0000000a,
    ExSkill01 = 0x0000000b,
    ExSkill02 = 0x0000000c,
    ExSkill03 = 0x0000000d,
    ExSkill04 = 0x0000000e,
    ExSkill05 = 0x0000000f,
    ExSkill06 = 0x00000010,
    ExSkill07 = 0x00000011,
    ExSkill08 = 0x00000012,
    ExSkill09 = 0x00000013,
    ExSkill10 = 0x00000014,
    Passive01 = 0x00000015,
    Passive02 = 0x00000016,
    Passive03 = 0x00000017,
    Passive04 = 0x00000018,
    Passive05 = 0x00000019,
    Passive06 = 0x0000001a,
    Passive07 = 0x0000001b,
    Passive08 = 0x0000001c,
    Passive09 = 0x0000001d,
    Passive10 = 0x0000001e,
    ExtraPassive01 = 0x0000001f,
    ExtraPassive02 = 0x00000020,
    ExtraPassive03 = 0x00000021,
    ExtraPassive04 = 0x00000022,
    ExtraPassive05 = 0x00000023,
    ExtraPassive06 = 0x00000024,
    ExtraPassive07 = 0x00000025,
    ExtraPassive08 = 0x00000026,
    ExtraPassive09 = 0x00000027,
    ExtraPassive10 = 0x00000028,
    Support01 = 0x00000029,
    Support02 = 0x0000002a,
    Support03 = 0x0000002b,
    Support04 = 0x0000002c,
    Support05 = 0x0000002d,
    Support06 = 0x0000002e,
    Support07 = 0x0000002f,
    Support08 = 0x00000030,
    Support09 = 0x00000031,
    Support10 = 0x00000032,
    EnterBattleGround = 0x00000033,
    LeaderSkill01 = 0x00000034,
    LeaderSkill02 = 0x00000035,
    LeaderSkill03 = 0x00000036,
    LeaderSkill04 = 0x00000037,
    LeaderSkill05 = 0x00000038,
    LeaderSkill06 = 0x00000039,
    LeaderSkill07 = 0x0000003a,
    LeaderSkill08 = 0x0000003b,
    LeaderSkill09 = 0x0000003c,
    LeaderSkill10 = 0x0000003d,
    Equipment01 = 0x0000003e,
    Equipment02 = 0x0000003f,
    Equipment03 = 0x00000040,
    Equipment04 = 0x00000041,
    Equipment05 = 0x00000042,
    Equipment06 = 0x00000043,
    Equipment07 = 0x00000044,
    Equipment08 = 0x00000045,
    Equipment09 = 0x00000046,
    Equipment10 = 0x00000047,
    PublicSkill01 = 0x00000048,
    PublicSkill02 = 0x00000049,
    PublicSkill03 = 0x0000004a,
    PublicSkill04 = 0x0000004b,
    PublicSkill05 = 0x0000004c,
    PublicSkill06 = 0x0000004d,
    PublicSkill07 = 0x0000004e,
    PublicSkill08 = 0x0000004f,
    PublicSkill09 = 0x00000050,
    PublicSkill10 = 0x00000051,
    GroupBuff01 = 0x00000052,
    HexaBuff01 = 0x00000053,
    EventBuff01 = 0x00000054,
    EventBuff02 = 0x00000055,
    EventBuff03 = 0x00000056,
    MoveAttack01 = 0x00000057,
    MetamorphNormalAttack = 0x00000058,
    GroundPassive01 = 0x00000059,
    GroundPassive02 = 0x0000005a,
    GroundPassive03 = 0x0000005b,
    GroundPassive04 = 0x0000005c,
    GroundPassive05 = 0x0000005d,
    GroundPassive06 = 0x0000005e,
    GroundPassive07 = 0x0000005f,
    GroundPassive08 = 0x00000060,
    GroundPassive09 = 0x00000061,
    GroundPassive10 = 0x00000062,
    HiddenPassive01 = 0x00000063,
    HiddenPassive02 = 0x00000064,
    HiddenPassive03 = 0x00000065,
    HiddenPassive04 = 0x00000066,
    HiddenPassive05 = 0x00000067,
    HiddenPassive06 = 0x00000068,
    HiddenPassive07 = 0x00000069,
    HiddenPassive08 = 0x0000006a,
    HiddenPassive09 = 0x0000006b,
    HiddenPassive10 = 0x0000006c,
    Count = 0x0000006d,
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

struct __declspec(align(8)) Battle__Fields
{
    // BattleLogicState__Enum state;
    struct LogicGameTime* _GameTime_k__BackingField;
    int64_t _StartTickRealTime_k__BackingField;
    int32_t _MaxDurationFrame_k__BackingField;
    struct IPseudoRandomService* _PseudoRandom_k__BackingField;

    struct
    Dictionary_2_System_ValueTuple_2_List_1_MX_Logic_BattleEntities_Obe0b78bdab1e49e02c2910c914876bf18bc9c40e0502cd86f581c8ab3bdb053d_
    * _PopulationGroups_k__BackingField;
    struct Dictionary_2_System_String_System_Int32_* RandomNumbers;
    struct BattleEntityIdProvider* _Provider_k__BackingField;

    struct BattleEventBroker* _EventBroker_k__BackingField;
    struct BattleSummary* _BattleSummary_k__BackingField;
    struct BattleSetting* _Setting_k__BackingField;
    double UnitType;
    double ResultValue;
    // StageTopography__Enum _StageTopography_k__BackingField;
    struct CharacterGroupTargetSideMapping* TargetSideMapping;
    struct PlayerGroup* playerGroup;
    struct Ground* _Ground_k__BackingField;

    int32_t _TotalEnemyCount_k__BackingField;
    int32_t _RemainEnemyCount_k__BackingField;
    struct HashSet_1_MX_Logic_BattleEntities_Obe0b78bdab1e49e02c2910c914876bf18bc9c40e0502cd86f581c8ab3bdb053d_*
    enemyToKill;
    bool _ImmuneHitBeforeTimeOutEnd_k__BackingField;
    bool _HideNPCWhenBattleEnd_k__BackingField;
    bool _CoverPointOff_k__BackingField;
    struct ExpirableObjectHolder_1_MX_Logic_Skills_LogicEffects_OverrideStageTopographyEffect_*
    stageTopographyExpirableObjectHolder;
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
