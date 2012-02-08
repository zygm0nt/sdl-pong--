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


#include <time.h>      // has the uclock() we need
#include "timer.h"


/*
 * constructor, in our case nothing needs to be done
 */
TIMER::TIMER()
{
   startTime = uclock();
};

/*
 * destructor, also nothing to do
 */
TIMER::~TIMER()
{
};

/*
 * hmm, this is pretty simple :)
 */
long long TIMER::getCount()
{
    return (uclock()-startTime);
};

