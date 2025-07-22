#include "pch.h"
#include "NoCost.h"

void NoCost::hProcessSkillCard(PlayerSkillCardManager* _this)
{
    // TODO: Enable field, GUI, etc.
    _this->CurCost(_this->MaxCost());
    _this->RegenStartDelayFrame(0);

    CALL_ORIGINAL(hProcessSkillCard, _this);
}

void NoCost::init()
{
    // TODO modularize this. im just busy rn
    HookManager::install(PlayerSkillCardManager::ProcessSkillCard(), hProcessSkillCard);
    LOG_INFO("NoCost feature initialized successfully.");
}
