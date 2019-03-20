#include <LPC21xx.H>

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
	IO1DIR=0x10000;
	IO1SET=0x10000;
	IO1CLR=0x10000;
	while(1)
		{
		IO1SET=0x10000;
		MsDelay(1000);
		IO1CLR=0x10000;
		MsDelay(1000);
		}
}
