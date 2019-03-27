#include <LPC21xx.H>

#define LEDOFF_bm = 0x00000
#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000
#define LED0123_bm 0x000f0000

//current excercise: 16

void MsDelay(iMsNumber)
{
	int iDelayIteration=0;
	int iDelayVariable=0;
	for(iDelayIteration=0; iDelayIteration<iMsNumber*4998; iDelayIteration++)
	{
		iDelayVariable++;
	}
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

int iReadButton1()
{
	IO0DIR=0x0;
	IO0SET=0x10;
	if(IO0PIN==0x10) return 1;
	else return 0;
}

int main()
{
	IO0DIR=0x0;
	IO0SET=0x10;
	IO1DIR=LED0123_bm;
	
	
	while(1)
		{
			//unsigned char iBut1State = iReadButton1();
			if((IO0PIN & 0x10 )== 0) IO1SET=LED0_bm;
			else IO1CLR=LED0123_bm;
			
			
			
			
			
			
			
			
			
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
			
			
/*			LedInit();
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
			IO1CLR=LED3_bm;*/
		}
}
