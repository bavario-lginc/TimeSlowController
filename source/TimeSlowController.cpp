#include "TimeSlowController.h"

TimeSlowController::TimeSlowController(const char *pName) : LiveActor(pName) {
    mDuration = -1; // No time limit
    mTimer = 0;
    mWillKill = false;
}
void TimeSlowController::initAfterPlacement() {
    MR::createTimeStopScreenEffect();
}
void TimeSlowController::init(const JMapInfoIter &rIter) {
    MR::useStageSwitchReadA(this, rIter);
    MR::useStageSwitchReadB(this, rIter);
    MR::initDefaultPos(this, rIter);
    MR::connectToSceneMapObjMovement(this);
    MR::invalidateClipping(this);
    MR::getJMapInfoArg0NoInit(rIter, &mDuration);
    MR::getJMapInfoArg1NoInit(rIter, &mWillKill);
    initNerve(&NrvTimeSlowController::NrvWait::sInstance, 0);
    makeActorAppeared();
}
void TimeSlowController::exeWait () {
    if (MR::isOnSwitchA(this)) {
        exeOnEffect();
        setNerve(&NrvTimeSlowController::NrvEffect::sInstance);
    }
}
void TimeSlowController::exeEffect () {
    if ((mDuration == -1 && !MR::isOnSwitchA(this)) || --mTimer == 0) {
        exeOffEffect();
        setNerve(&NrvTimeSlowController::NrvWait::sInstance);
    }
}
void TimeSlowController::exeOnEffect() {
    if (mDuration != -1) // Time limit
        mTimer = mDuration;
    MR::onTimeStopScreenEffect();
    MR::onSwitchB(this);
}
void TimeSlowController::exeOffEffect() {
    MR::offTimeStopScreenEffect();
    MR::offSwitchB(this);
    if (mWillKill) 
        kill();
}

namespace NrvTimeSlowController {
    void NrvWait::execute(Spine *pSpine) const {
        ((TimeSlowController *)pSpine->mExecutor)->exeWait();
    }
    void NrvEffect::execute(Spine *pSpine) const {
        ((TimeSlowController *)pSpine->mExecutor)->exeEffect();
    }

    NrvWait(NrvWait::sInstance);
    NrvEffect(NrvEffect::sInstance);
}