#include <LPC21xx.H>
#include "timer.h"

#define TIME0_ON_bm 1
#define TIME0_RESET_bm (1 << 1)
#define TIMER0_MR0_RESET_bm (1<<1)
#define TIMER0_MR0_INTERRUPT_bm 1
#define TIMER0_MR0_STOP_bm (1<<2)

void InitTimer0(void)
{
	T0TCR = TIME0_ON_bm;
}

void WaitOnTimer0( unsigned int uiTime )
{
	T0TCR = (T0TCR | TIME0_RESET_bm);
	T0TCR = TIME0_ON_bm;
	while ( T0TC < (15*uiTime) ) {}
}

void InitTimer0Match0( unsigned int iDelayTime )
{
	T0MR0 = 0xF*iDelayTime;
	T0MCR = (TIMER0_MR0_RESET_bm | TIMER0_MR0_INTERRUPT_bm);
	T0TCR = TIME0_RESET_bm;
	T0TCR = TIME0_ON_bm;
}

void WaitOnTimer0Match0()
{
	while ( (T0IR & 1) == 0) {}
	T0IR = (T0IR | 1);
}
