/**************************************************************
* FILE:         ADC_drv.c
* DESCRIPTION:  A/D driver for piccolo devices
* AUTHOR:       Mitja Nemec
*
****************************************************************/
#ifndef     __ADC_DRV_H__
#define     __ADC_DRV_H__

#include    "DSP28x_Project.h"

// doloci kateri PWM modul prozi ADC
#define     ADC_MODUL1      EPwm7Regs

// kje se nahajajo rezultati
#define     ADC_RESULT0     (AdcResult.ADCRESULT0)
#define     NAPETOST        (AdcResult.ADCRESULT1)

/**************************************************************
* inicializiramo ADC
**************************************************************/
extern void ADC_init(void);

/**************************************************************
* Funkcija, ki pocaka da ADC konca s pretvorbo
* vzorcimo...
* return: void
**************************************************************/
extern void ADC_wait(void);

#endif /* __ADC_DRV_H__ */
