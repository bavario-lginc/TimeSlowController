#include "TimeSlowController.h"

TimeSlowController::TimeSlowController(const char *pName) : LiveActor(pName)
{
    executeOn = false;
}
void TimeSlowController::initAfterPlacement()
{
    MR::createTimeStopScreenEffect();
    OSReport("Effect created\n");
}
void TimeSlowController::init(const JMapInfoIter &rIter)
{
    OSReport("Hello there\n");
    MR::useStageSwitchReadA(this, rIter);
    OSReport("Works 1\n");
    MR::useStageSwitchReadB(this, rIter);
    OSReport("Works 2\n");
    MR::initDefaultPos(this, rIter);
    OSReport("Works 3\n");
    MR::connectToSceneMapObjMovement(this);
    OSReport("Works 4\n");
    MR::invalidateClipping(this);
    OSReport("Works 5\n");
    MR::getJMapInfoArg0NoInit(rIter, &mTimer);
    MR::getJMapInfoArg1NoInit(rIter, &willKill);
    OSReport("Works 6\n");
    cTimer = mTimer;
    makeActorAppeared();
    OSReport("Works 7\n");
}
void TimeSlowController::control()
{
    OSReport("I'm being controlled\n");
    if (mTimer != -1)
    {
        if (MR::isOnSwitchA(this))
        {
            if (!executeOn)
            {
                MR::onTimeStopScreenEffect();
                MR::onSwitchB(this);
                OSReport("A is ON\n");
                executeOn = true;
            }
            else if (!cTimer)
            {
                MR::offTimeStopScreenEffect();
                MR::offSwitchB(this);
                OSReport("A is OFF\n");
                executeOn = true;
                if (willKill > 0)
                    kill();
                cTimer = mTimer;
            }
            else
                cTimer--;
        }
    }
    else
    {
        if (MR::isOnSwitchA(this) && !executeOn)
        {
            MR::onTimeStopScreenEffect();
            MR::onSwitchA(this);
            executeOn = true;
            OSReport("B is ON\n");
        }
        if (!MR::isOnSwitchA(this) && executeOn)
        {
            MR::offTimeStopScreenEffect();
            MR::offSwitchB(this);
            OSReport("B is OFF\n");
            executeOn = false;
            if (willKill > 0)
                kill();
        }
    }
}