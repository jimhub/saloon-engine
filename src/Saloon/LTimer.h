/*
 * LTimer.h
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#ifndef LTIMER_H_
#define LTIMER_H_

#include <SDL2/SDL.h>

//The application time based timer
class LTimer
{
private:
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;

    public:
    //Initializes variables
    LTimer();

    //The various clock actions
    void start();
    void stop();
    void reset();
    void pause();
    void unpause();

    //Gets the timer's time
    Uint32 getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();
};


#endif /* LTIMER_H_ */
