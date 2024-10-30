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
    s32 hTiner;
    s32 zTimer;
 
    bool willKill;
    bool wasOnSwitchFlag;
    bool executeOn;
};
