#include "TimeSlowController.h"

TimeSlowController::TimeSlowController(const char *pName) : LiveActor(pName)
{
    executeOn = false;
    wasOnSwitchFlag = false;
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
    MR::getJMapInfoArg2NoInit(rIter, &hTimer);
    cTimer = mTimer;
    makeActorAppeared();
}
void TimeSlowController::control()
{
if (!zTimer)
{
  if (MR::isOnSwitchA(this))
    wasOnSwitchFlag = true; 
// If I don't use a flag the object can be broken if SW_A is disabled in the middle of the action
    if (mTimer != -1 && wasOnSwitchFlag)
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
            MR::offSwitchA(this);
            
            zTimer = hTimer;
            wasOnSwitchFlag = false;
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

            zTimer = hTimer;
            executeOn = false;
            if (willKill)
                kill();
        }
    }
}
}
else
 zTimer--;