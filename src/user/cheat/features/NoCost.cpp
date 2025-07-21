#include "pch.h"
#include "NoCost.h"

#include "appdata/types.h"

void hProcessSkillCard(PlayerSkillCardManager* _this)
{
    // LOG_DEBUG("_MaxCost_k__BackingField %f", _this->_MaxCost_k__BackingField);
    // LOG_DEBUG("_CurCost_k__BackingField %f", _this->_CurCost_k__BackingField);
    // LOG_DEBUG("_FeverChargeScale_k__BackingField %f", _this->_FeverChargeScale_k__BackingField);
    // LOG_DEBUG("_CostPerFrame_k__BackingField %f", _this->_CostPerFrame_k__BackingField);
    // LOG_DEBUG("_IsShuffle_k__BackingField %s", (_this->_IsShuffle_k__BackingField ? "true" : "false"));
    //
    // LOG_DEBUG("_RegenStartDelayFrame_k__BackingField %ld", _this->_RegenStartDelayFrame_k__BackingField);
    // LOG_DEBUG("_IsMainPlayerSkillCard_k__BackingField %s", (_this->_IsMainPlayerSkillCard_k__BackingField ? "true" : "false"));
    // LOG_DEBUG("_RegenCostBefore_k__BackingField %f", _this->_RegenCostBefore_k__BackingField);

    // TODO: Enable field, GUI, etc.
    _this->_CurCost_k__BackingField = _this->_MaxCost_k__BackingField;
    
    CALL_ORIGINAL(hProcessSkillCard, _this);
}


void NoCost::Init()
{
    // TODO modularize this. im just busy rn
    PlayerSkillCardManager::ProcessSkillCard = App::getMethod("BlueArchive.dll", "PlayerSkillCardManager", "ProcessSkillCard")->Cast<void, PlayerSkillCardManager*>();

    HookManager::install(PlayerSkillCardManager::ProcessSkillCard, hProcessSkillCard);
    LOG_INFO("NoCost feature initialized successfully.");
}
