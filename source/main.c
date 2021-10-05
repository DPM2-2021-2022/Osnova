/****************************************************************
* FILENAME:     main.c
* DESCRIPTION:  initialization code
* AUTHOR:       Mitja Nemec
*
****************************************************************/
#include "main.h"

// Global variables
long sum = 0;
long difference;

// function declaration
void foo(int a, int b);

/**************************************************************
* main function only executes initialization code
**************************************************************/
void main(void)
{/*
    // local variables
    int x = 2;
    int y = 7;
    long product;
    float counter;
    int for_loop_passage_counter = 0;
    float a, b;

    // Setting the sum and difference for no reason
    sum = 5;
    difference = 6;

    // get sum and difference through function call
    foo(x, y);

    // multiply
    product = x*y;

    // example of problems with floats
    for(counter = 0.1; counter <= 1; counter = counter + 0.1)
    {
        for_loop_passage_counter = for_loop_passage_counter + 1;
    }

    // another example of problems with floats
    for_loop_passage_counter = 0;
    for(counter = 100000001.0; counter <= 100000010.0; counter = counter + 1)
    {
        for_loop_passage_counter = for_loop_passage_counter + 1;
    }
    
    // demonstration of volatile keyword
    while(x == 2)
    {
        // DO NOTHING
        asm(" NOP");
    }
*/
    // initialize system clock
    InitSysCtrl();
    
    // default GPIO initialization
    InitGpio();

    // initialize PIE expansion unit
    InitPieCtrl();

    // populate vector table with dummy interrupt functions
    InitPieVectTable();

    // initialize ADC and PWM
    ADC_init();
    PWM_init();

    // initialize specific GPIO functions
    PCB_init();

    // initialize periodic interrupt function
    PER_int_setup();

    // enable interrupts
    EINT;
    ERTM;

    // start timer, which will trigger ADC and an interrupt
    PWM_start();

    // proceed to background loop code
    BACK_loop();
}   // end of main

/**************************************************************
* foo function definition
**************************************************************/
void foo(int a, int b)
{
    sum = a + b;
    difference = a - b;
}
