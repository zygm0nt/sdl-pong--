/*
 *                          The Art Of
 *                      D E M O M A K I N G
 *
 *
 *                     by Alex J. Champandard
 *                          Base Sixteen
 *
 *
 *                http://www.flipcode.com/demomaking
 *
 *                This file is in the public domain.
 *                      Use at your own risk.
 */


#ifndef __TIMER_H_
#define __TIMER_H_

class TIMER
{
   public:

// startup the timer
   TIMER();
// shut down the timer
   ~TIMER();

// return the value of the current couter
   long long getCount();

   private:

   long long startTime;

};

#endif
