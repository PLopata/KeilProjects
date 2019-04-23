#include <LPC21xx.H>

#define LEDOFF_bm = 0x00000
#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000
#define LED0123_bm 0x000f0000



//current excercise: 20
//enum ButtonState {RELEASD, PRESSED} eButtonState;

enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3} eButtonState;

void MsDelay(iMsNumber)
{
	int iDelayIteration=0;
	int iDelayVariable=0;
	for(iDelayIteration=0; iDelayIteration<iMsNumber*4998; iDelayIteration++)
	{
		iDelayVariable++;
	}
}

void KeyboardInit()
{
	IO0DIR=(IO0DIR & ~(0xf0));
}

void LedInit()
{
	IO1DIR=(IO1DIR | LED0123_bm);
	IO1CLR=LED0123_bm;
	IO1SET=LED0_bm;
}

void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR=LED0123_bm;
	if(ucLedIndeks=='0') IO1SET=LED0_bm;
	else if(ucLedIndeks=='1') IO1SET=LED1_bm;
	else if(ucLedIndeks=='2') IO1SET=LED2_bm;
	else if(ucLedIndeks=='3') IO1SET=LED3_bm;
}
/*
enum ButtonState eReadButton1()
{
	//IO0DIR=IO0DIR &(~0x10);
	if((IO0PIN & 0x10) != 0) return RELEASD;
	else return PRESSED;
}
*/

enum KeyboardState eReadButton()
{
	if ((IO0PIN & 0x10) == 0) return BUTTON_0;
	else if ((IO0PIN & 0x40) == 0) return BUTTON_1;
	else if ((IO0PIN & 0x20) == 0) return BUTTON_2;
	else if ((IO0PIN & 0x80) == 0) return BUTTON_3;
	else return RELEASED;
}

int main()
{
	IO1DIR=LED0123_bm;
	KeyboardInit();
	while(1)
		{
			eButtonState=eReadButton();
			
			switch (eButtonState)
				{
					case BUTTON_0:
						IO1CLR=LED0123_bm;
						IO1SET=LED0_bm;
						break;
					case BUTTON_1:
						IO1CLR=LED0123_bm;
						IO1SET=LED1_bm;
						break;
					case BUTTON_2:
						IO1CLR=LED0123_bm;
						IO1SET=LED2_bm;
						break;
					case BUTTON_3:
						IO1CLR=LED0123_bm;
						IO1SET=LED3_bm;
						break;
					case RELEASED:
						IO1CLR=LED0123_bm;
						break;
				}
			
			/*
			if (eButtonState == PRESSED)
			{
				IO1CLR=LED0123_bm;
				IO1SET=LED1_bm;
			}
			else 
			{	
				IO1CLR=LED0123_bm;
				IO1SET=LED0_bm;
			}
				
			*/
			
			/*
			LedInit();
			MsDelay(250);
			LedOn('1');
			MsDelay(250);
			LedOn('2');
			MsDelay(250);
			LedOn('3');
			MsDelay(250);
			*/
			
			/*
			LedInit();
			MsDelay(250);
			IO1CLR=LED0_bm;
			IO1SET=LED1_bm;
			MsDelay(250);
			IO1CLR=LED1_bm;
			IO1SET=LED2_bm;
			MsDelay(250);
			IO1CLR=LED2_bm;
			IO1SET=LED3_bm;
			MsDelay(250);
			IO1CLR=LED3_bm;
			*/
		}
}