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

int main()
{
	LedInit();
	KeyboardInit();
	while(1)
		{
			switch (eReadButton())
				{
					case BUTTON_1:
						LedStepRight();
						break;
					case BUTTON_2:
						LedStepLeft();
						break;
					default :
						break;
				}
			MsDelay(250);
		}
}

