#pragma once
#include "syati.h"

class TimeSlowController : public LiveActor {
public:
    TimeSlowController(const char *pName);
    virtual void init(const JMapInfoIter &rIter);
    virtual void initAfterPlacement();
    void exeWait();
    void exeEffect();
    void exeOnEffect();
    void exeOffEffect();
    s32 mDuration;
    s32 mTimer;
    bool mWillKill;
};

namespace NrvTimeSlowController {
    NERVE(NrvWait);
    NERVE(NrvEffect);
};