#include "TimeSlowController.h"

TimeSlowController::TimeSlowController(const char *pName) : LiveActor(pName)
{
    executeOn = false;
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
    if (MR::isOnSwitchA(this))
    {
        if (!executeOn)
        {
            MR::onTimeStopScreenEffect();
            executeOn = true;
        }
        else if (!cTimer)
        {
            MR::offTimeStopScreenEffect();
            executeOn = true;
            if (willKill > 0)
                kill();
            cTimer = mTimer;
        }
        else
            cTimer--;
    }
    else if (MR::isOnSwitchB(this) && !executeOn)
    {
        MR::onTimeStopScreenEffect();
        executeOn = true;
    }
    if (!MR::isOnSwitchB(this) && executeOn)
    {
        MR::offTimeStopScreenEffect();
        executeOn = false;
        if (willKill > 0)
            kill();
    }
}