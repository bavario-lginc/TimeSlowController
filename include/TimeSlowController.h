#pragma once
#include "syati.h"

class TimeSlowController : public LiveActor {
public:
    TimeSlowController(const char *pName);
    virtual void init(const JMapInfoIter &rIter);
    virtual void control();
    virtual void initAfterPlacement();

    s32 effectTimer;
    s32 countableEffectTimer;
    s32 cooldownTimer;
    s32 countableCooldownTimer;
 
    bool willKill;
    bool wasOnSwitchFlag;
    bool executeOn;
};
