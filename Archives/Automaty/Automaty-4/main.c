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

enum LedState {WAIT, LED_RIGHT_3} eLedState;
enum LedState eLedState = LED_RIGHT_3;

unsigned char ucStepCounter=0;

int main()
{
	LedInit();
	KeyboardInit();
	while(1)
		{
			switch (eLedState)
				{
					case LED_RIGHT_3:
						if ( ucStepCounter == 3 )
						{
							eLedState = WAIT;
							ucStepCounter = 0;
						}
						else
						{
							ucStepCounter++;
							LedStepRight();
							MsDelay(350);
						}
						break;
					case WAIT:
						if ( eReadButton() == BUTTON_0 )
						{
							eLedState = LED_RIGHT_3;
						}
						break;
				}
		}
}

