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

enum LedState {WAIT, LED_RIGHT} eLedState;
enum LedState eLedState = LED_RIGHT;

int main()
{
	LedInit();
	KeyboardInit();
	while(1)
		{
			switch (eLedState)
				{
					case LED_RIGHT:
						if ( eReadButton() == BUTTON_0 )
						{
							eLedState = WAIT;
						}
						else 
						{
							LedStepRight();
							MsDelay(250);
						}
						break;
					case WAIT:
						if ( eReadButton() == BUTTON_1 )
						{
							eLedState = LED_RIGHT;
						}
						break;
				}
		}
}

