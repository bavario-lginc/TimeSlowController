#pragma once
#include "syati.h"

class TimeSlowController : public LiveActor {
public:
    TimeSlowController(const char *pName);
    virtual void init(const JMapInfoIter &rIter);
    virtual void control();
    virtual void initAfterPlacement();

    s32 mTimer;
    s32 cTimer;
    
    bool wasOnSwitchB;
    bool willKill;
    bool executeOn;
};
