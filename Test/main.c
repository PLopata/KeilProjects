#include <LPC21xx.H>

#define LEDOFF_bm = 0x00000
#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000
#define LED03_bm 0xf0000

void MsDelay(iMsNumber)
{
	int iDelayIteration=0;
	int iDelayVariable=0;
	for(iDelayIteration=0; iDelayIteration<iMsNumber*4998; iDelayIteration++)
	{
		iDelayVariable++;
	}
	
}

int main()
{
	/*IO1DIR=LED03_bm;
	IO1SET=LED0_bm;
	IO1CLR=LED0_bm;
	IO1SET=LED1_bm;
	IO1CLR=LED1_bm;
	IO1SET=LED2_bm;
	IO1CLR=LED2_bm;
	IO1SET=LED3_bm;
	IO1CLR=LED3_bm;
	IO1SET=LED03_bm;*/
	
	while(1)
		{
			int LedNr;
			IO1DIR=LED03_bm;
			for(iLedNr=0; iLedNr<4; iLedNr++)
			{
				
			}
		}
}
