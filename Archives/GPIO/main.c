#include <LPC21xx.H>

#define LED0_bm 0x10000 
#define LED1_bm 0x20000 
#define LED2_bm 0x40000 
#define LED3_bm 0x80000 

#define S0_bm 0x10 
#define S1_bm 0x40 
#define S2_bm 0x20 
#define S3_bm 0x80 

void KeyboardInit()
{
	IO0DIR=(IO0DIR & ~(S0_bm | S1_bm | S2_bm | S3_bm));
}

enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum KeyboardState eReadButton()
{
	if ((IO0PIN & S0_bm) == 0) 
	{
		return BUTTON_0;
	}
	else if ((IO0PIN & S1_bm) == 0) //wcisniety-> 0x00 puszczony-> 0x40
	{
		return BUTTON_1;
	}
	else if ((IO0PIN & S2_bm) == 0) //wcisniety-> 0x00 puszczony-> 0x20
	{
		return BUTTON_2;
	}
	else if ((IO0PIN & S3_bm) == 0) 
	{
		return BUTTON_3;
	}
	else 
	{
		return RELEASED;
	}
}

void LedInit()
{
	IO1DIR=(IO1DIR | LED0_bm | LED1_bm | LED2_bm |LED3_bm);
	IO1CLR=(LED0_bm | LED1_bm | LED2_bm |LED3_bm);
	IO1SET=LED0_bm;
}

void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR=(LED0_bm | LED1_bm | LED2_bm |LED3_bm);
	switch(ucLedIndeks)
	{
		case 0:
			IO1SET=LED0_bm;
			break;
		case 1:
			IO1SET=LED1_bm;
			break;
		case 2:
			IO1SET=LED2_bm;
			break;
		case 3:
			IO1SET=LED3_bm;
	}
}

enum Direction {LEFT, RIGHT};

void LedStep(enum Direction eDirection)
{
	static unsigned int uiLedPointer=0; 
	if( eDirection == LEFT)
	{
		uiLedPointer=(uiLedPointer+1)%4;
		LedOn(uiLedPointer);
	}
	else
	{
		uiLedPointer=(uiLedPointer-1)%4;
		LedOn(uiLedPointer);	
	}
}

void LedStepLeft()
{
	LedStep(LEFT);
}

void LedStepRight()
{
	LedStep(RIGHT);
}

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
			//MsDelay(250);
		}
}
