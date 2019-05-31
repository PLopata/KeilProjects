#include "led.h"
#include "timer_interrupts.h"

int main (){
	unsigned int iMainLoopCtr;
	Timer0Interrupts_Init(250000, &LedStepRight );

	while(1)
	{
	 	iMainLoopCtr++;
	}
}
