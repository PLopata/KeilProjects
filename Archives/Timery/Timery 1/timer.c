#include <LPC21xx.H>
#include "timer.h"

#define T0TC_ON_bm 1
#define T0TC_RESET_bm (1 << 1)

void InitTimer0(void)
{
	T0TCR = T0TC_ON_bm;
}

void WaitOnTimer0( unsigned int uiTime )
{
	unsigned char ucMicrosecondsConverter = 0xF;
	
	T0TCR = T0TC_RESET_bm;
	T0TCR = T0TC_ON_bm;
	while ( T0TC < (ucMicrosecondsConverter*uiTime) ) {}
}
