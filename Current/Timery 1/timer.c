#include <LPC21xx.H>
#include "timer.h"

#define TIME0_ON_bm 1
#define TIME0_RESET_bm (1 << 1)

void InitTimer0(void)
{
	T0TCR = TIME0_ON_bm;
}

void WaitOnTimer0( unsigned int uiTime )
{
	T0TCR = (T0TCR | TIME0_RESET_bm);
	T0TCR = TIME0_ON_bm;
	while ( T0TC < (0xF*uiTime) ) {}
}
