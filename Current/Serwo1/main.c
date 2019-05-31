#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"

#define DETECTOR_bm (1<<10)

void DetectorInit()
{
	IO0DIR = ( IO0DIR & (~DETECTOR_bm) );
}

enum DetectorState {INACTIVE, ACTIVE};

enum DetectorState eReadDetector()
{
	if ( (IO0PIN & DETECTOR_bm) == 0)
	{
		return ACTIVE;
	}
	else 
	{
		return INACTIVE;
	}
}

void Automat(void)
{
	static enum State {CALLIB, LED_LEFT, LED_RIGHT, WAIT} eLedState = CALLIB;

	switch ( eLedState )
	{
		case CALLIB:
		{
			if ( eReadDetector() == INACTIVE )
			{
				eLedState = CALLIB;
				LedStepLeft();
			}
			else 
			{
				eLedState = WAIT;
			}
			break;
		}
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
	DetectorInit();
	Timer0Interrupts_Init(40000, &Automat );

	while(1)
	{
		iMainLoopCtr++;
	}
}
