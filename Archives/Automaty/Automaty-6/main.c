#include "led.h"
#include "keyboard.h"

void MsDelay(int iMsNumber)
{
	int iMsConstant=4998;
	int iDelayIteration=0;
	int iDelayVariable=0;
	for(iDelayIteration=0; iDelayIteration<iMsNumber*iMsConstant; iDelayIteration++)
	{
		iDelayVariable++;
	}
}

enum LedState {WAIT, WAIT10, LED_RIGHT, LED_LEFT} eLedState;
enum LedState eLedState = WAIT;

unsigned char ucWaitCounter=0;

int main()
{
	LedInit();
	KeyboardInit();
	while(1)
		{
			switch (eLedState)
				{
					case LED_LEFT:
						if ( eReadButton() == BUTTON_1 )
						{
							eLedState = WAIT;
						}
						else if ( eReadButton() == BUTTON_3 )
						{
							eLedState = WAIT10;
						}
						else 
						{
							LedStepLeft();
						}
						break;
					case LED_RIGHT:
						if ( eReadButton() == BUTTON_1 )
						{
							eLedState = WAIT;
						}
						else 
						{
							LedStepRight();
						}
						break;
					case WAIT:
						if ( eReadButton() == BUTTON_0 )
						{
							eLedState = LED_LEFT;
						}
						else if ( eReadButton() == BUTTON_2 )
						{
							eLedState = LED_RIGHT;
						}
						break;
					case WAIT10:
						if ( ucWaitCounter == 9 )
						{
							eLedState = LED_RIGHT;
							ucWaitCounter = 0;
						}
						else
						{
							ucWaitCounter++;
						}
						break;
				}
				MsDelay(100);
		}
}

