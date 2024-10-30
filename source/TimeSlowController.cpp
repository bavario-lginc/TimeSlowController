#include "TimeSlowController.h"

TimeSlowController::TimeSlowController(const char *pName) : LiveActor(pName)
{
    executeOn = false;
    willKill = false;
}
void TimeSlowController::initAfterPlacement()
{
    MR::createTimeStopScreenEffect();
}
void TimeSlowController::init(const JMapInfoIter &rIter)
{
    MR::useStageSwitchReadA(this, rIter);
    MR::useStageSwitchReadB(this, rIter);
    MR::initDefaultPos(this, rIter);
    MR::connectToSceneMapObjMovement(this);
    MR::invalidateClipping(this);
    MR::getJMapInfoArg0NoInit(rIter, &mTimer);
    MR::getJMapInfoArg1NoInit(rIter, &willKill);
    cTimer = mTimer;
    makeActorAppeared();
}
void TimeSlowController::control()
{
    if (mTimer != -1 && MR::isOnSwitchA(this))
    {
        if (!executeOn)
        {
            MR::onTimeStopScreenEffect();
            MR::onSwitchB(this);
            executeOn = true;
        }
        else if (!cTimer)
        {
            MR::offTimeStopScreenEffect();
            MR::offSwitchB(this);
            
            executeOn = false;
            if (willKill)
                kill();
            cTimer = mTimer;
        }
        else
            cTimer--;
    }
    else
    {
        if (MR::isOnSwitchA(this) && !executeOn)
        {
            MR::onTimeStopScreenEffect();
            MR::onSwitchA(this);
            executeOn = true;
        }
        if (!MR::isOnSwitchA(this) && executeOn)
        {
            MR::offTimeStopScreenEffect();
            MR::offSwitchB(this);

            executeOn = false;
            if (willKill)
                kill();
        }
    }
}
