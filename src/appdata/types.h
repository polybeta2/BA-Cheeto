#pragma once

#pragma pack(8)

class SkillCardManager
{
public:
    char _pad1[0x38];
};

class CostSkillCardManager : public SkillCardManager
{
public:
    float _MaxCost_k__BackingField;
    float _CurCost_k__BackingField;
    float _FeverChargeScale_k__BackingField;
    float _CostPerFrame_k__BackingField;
    bool _IsShuffle_k__BackingField; // 0x48
    char _pad1[0x3]; // _FeverInfo_k__BackingField // 0x4c
    char _pad2[0x14]; // _FeverInfo_k__BackingField // 0x4c
    long _RegenStartDelayFrame_k__BackingField; // 0x60
    bool _IsMainPlayerSkillCard_k__BackingField; // 0x68
    float _RegenCostBefore_k__BackingField; // 0x6c
    
};

class PlayerSkillCardManager : public CostSkillCardManager {
public:
    char _pad1[0xb0];
    inline static UnityResolve::MethodPointer<void, PlayerSkillCardManager*> ProcessSkillCard{};
};

#pragma pack()