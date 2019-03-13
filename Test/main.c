#include <LPC21xx.H>

void delay()
{
	int i=0;
	int a=0;
	for(i=0; i<12000; i++)
	{
		a++;
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
		delay();
		IO1CLR=0x10000;
		delay();
		}
}
