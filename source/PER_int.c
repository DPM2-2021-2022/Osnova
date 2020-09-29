/****************************************************************
* FILENAME:     PER_int.c
* DESCRIPTION:  periodic interrupt code
* AUTHOR:       Mitja Nemec
*
****************************************************************/
#include    "PER_int.h"
#include    "TIC_toc.h"

// variables required for voltage measurement
long voltage_raw = 0;
long voltage_offset = 0;
float voltage_gain = 3.3 / 4096;
float voltage = 0.0;

// PWM duty cycle
float duty = 0.0;

// variables for generating reference value
float ref_counter = 0;
float ref_counter_prd = SWITCH_FREQ;
float ref_counter_cmpr = 500;

float ref_value = 0;
float ref_value_high = 0.5;
float ref_value_low = 0.05;

// CPU load estimation
float   cpu_load  = 0.0;
long    interrupt_cycles = 0;

// counter of too long interrupt function executions
int interrupt_overflow_counter = 0;

/**************************************************************
* interrupt funcion
**************************************************************/
#pragma CODE_SECTION(PER_int, "ramfuncs");
void interrupt PER_int(void)
{
    // local variables
    
    // acknowledge interrupt within PWM module
    EPwm7Regs.ETCLR.bit.INT = 1;
    // acknowledge interrupt within PIE module
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    
    // start CPU load stopwatch
    interrupt_cycles = TIC_time;
    TIC_start();

    // get previoust CPU load estimate
    cpu_load = (float)interrupt_cycles / (CPU_FREQ/SWITCH_FREQ);

    // wait for the ADC to finish with conversion
    ADC_wait();

    // calculate voltage measured from ADC data
    voltage_raw = NAPETOST;
    voltage = voltage_raw * voltage_gain;

    // generate reference value
    ref_counter = ref_counter + 1;
    if (ref_counter >= ref_counter_prd)
    {
        ref_counter = 0;
    }
    if (ref_counter > ref_counter_cmpr)
    {
        ref_value = ref_value_low;
    }
    else
    {
        ref_value = ref_value_high;
    }


    duty = ref_value;

    // refresh PWM duty cycle
    PWM_update(duty);

    // store values for display within CCS
    DLOG_GEN_update();

    /* Test if new interrupt is already waiting.
     * If so, then something is seriously wrong.
     */
    if (EPwm7Regs.ETFLG.bit.INT == TRUE)
    {
        // count number of interrupt overflow events
        interrupt_overflow_counter = interrupt_overflow_counter + 1;
        
        /* if interrupt overflow event happened more than 10 times
         * stop the CPU
         *
         * Better solution would be to properly handle this event
         * (shot down the power stage, ...)
         */
        if (interrupt_overflow_counter >= 10)
        {
            asm(" ESTOP0");
        }
    }
    
    // stop the sCPU load stopwatch
    TIC_stop();

}   // end of PWM_int

/**************************************************************
* Function which initializes all required for execution of
* interrupt function
**************************************************************/
void PER_int_setup(void)
{
    // initialize data logger
    dlog.trig_value = SWITCH_FREQ - 10;     // specify trigger value
    dlog.slope = Positive;                  // trigger on positive slope
    dlog.prescalar = 1;                     // store every  sample
    dlog.mode = Normal;                     // Normal trigger mode
    dlog.auto_time = 100;                   // number of calls to update function
    dlog.holdoff_time = 100;                // number of calls to update function

    dlog.trig = &ref_counter;               // use reference generator counter as a trigger
    dlog.iptr1 = &voltage;                 // CH1 stores measured voltage

    // setup interrupt trigger
    EPwm7Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
    EPwm7Regs.ETPS.bit.INTPRD = ET_1ST;
    EPwm7Regs.ETCLR.bit.INT = 1;
    EPwm7Regs.ETSEL.bit.INTEN = 1;

    // register the interrupt function
    EALLOW;
    PieVectTable.EPWM7_INT = &PER_int;
    EDIS;

    // acknowledge any spurious interrupts
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

    // enable interrupt within PIE
    PieCtrlRegs.PIEIER3.bit.INTx7 = 1;

    // enable interrupt within CPU
    IER |= M_INT3;

    // enable interrupt in real time mode
    SetDBGIER(M_INT3);
}
