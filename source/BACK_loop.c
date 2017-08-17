/****************************************************************
* FILENAME:     BACK_loop.c
* DESCRIPTION:  background code
* AUTHOR:       Mitja Nemec
*
****************************************************************/

#include "BACK_loop.h"

// declaration of static global variables


// declaration of exxternal variables


// function prototypes

/**************************************************************
* Function which executes background loop code
**************************************************************/
#pragma CODE_SECTION(BACK_loop, "ramfuncs");
void BACK_loop(void)
{
    // local variables


    // infinite background loop
    while (1)
    {
        // handy for placing brakpoint
        asm(" NOP");


    }   // end of while(1)
}       // end of BACK_loop
