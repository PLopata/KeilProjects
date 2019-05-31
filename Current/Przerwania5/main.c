#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"

void Automat(void)
{
	static enum State {LED_LEFT, LED_RIGHT, WAIT} eLedState = LED_LEFT;

	switch ( eLedState )
	{
		case LED_LEFT:
		{
			if ( eReadButton() == BUTTON_1 )
			{
				eLedState = WAIT;
			}
			else 
			{
				eLedState = LED_LEFT;
				LedStepLeft();
			}
			break;
		}
		case LED_RIGHT:
		{
			if ( eReadButton() == BUTTON_1 )
			{
				eLedState = WAIT;
			}
			else 
			{
				eLedState = LED_RIGHT;
				LedStepRight();
			}
			break;
		}
		case WAIT:
		{
			if ( eReadButton() == BUTTON_0 )
			{
				eLedState = LED_LEFT;
			}
			else if ( eReadButton() == BUTTON_2 )
			{
				eLedState = LED_RIGHT;
			}
			else 
			{
				eLedState = WAIT;
			}
			break;
		}
	}
}

int main ()
{
	unsigned int iMainLoopCtr;
	LedInit();
	Timer0Interrupts_Init(20000, &Automat );

	while(1)
	{
	 	iMainLoopCtr++;
	}
}
