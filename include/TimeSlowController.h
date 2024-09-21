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
    s32 willKill;
    bool executeOn;
};