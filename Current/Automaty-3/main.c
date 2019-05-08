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

enum LedState {LED_LEFT, LED_RIGHT} eLedState;
enum LedState eLedState = LED_LEFT;

unsigned char ucStepCounter=0;

int main()
{
	LedInit();
	KeyboardInit();
	while(1)
		{
			switch (eLedState)
				{
					case LED_LEFT:
						if ( ucStepCounter < 2 )
						{
							ucStepCounter++;
							LedStepLeft();
						}
						else
						{
							LedStepLeft();
							ucStepCounter = 0;
							eLedState = LED_RIGHT;
						}
						break;
					case LED_RIGHT:
						if ( ucStepCounter < 2 )
						{
							ucStepCounter++;
							LedStepRight();
						}
						else
						{
							LedStepRight();
							ucStepCounter = 0;
							eLedState = LED_LEFT;
						}
						break;
				}
			MsDelay(250);
		}
}

