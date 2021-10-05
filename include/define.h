/****************************************************************
* FILENAME:     define.h           
* DESCRIPTION:  file with global define macros
* AUTHOR:       Mitja Nemec
*
****************************************************************/
#ifndef     __DEFINE_H__
#define     __DEFINE_H__

#include    "IQmathLib.h"

// PWM frequency
#define     SWITCH_FREQ     100000

// ratio between PWM and sampling frequency
#define   	SAMP_PRESCALE   1

// sampling frequency
#define   	SAMPLE_FREQ     (SWITCH_FREQ/SAMP_PRESCALE)

// sampling period
#define     SAMPLE_TIME     (1.0/SAMPLE_FREQ)

// CPU frequency
#define     CPU_FREQ        80000000

// Math constants
#define		SQRT3			1.7320508075688772935274463415059
#define		SQRT2			1.4142135623730950488016887242097
#define		PI				3.1415926535897932384626433832795

// bool type
typedef enum {FALSE = 0, TRUE} bool;

// behaviour of peripherals when CPU stops at debug event
// 0 stop immediately, 1 stop when finished, 2 run free
#define     DEBUG_STOP      0

#endif // end of __DEFINE_H__ definition
