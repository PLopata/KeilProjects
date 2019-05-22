#include <LPC21xx.H>

#include "led.h"
#include "keyboard.h"
#include "timer.h"

int main()
{
	LedInit();
	KeyboardInit();
	InitTimer0Match0(250000);
	while(1)
		{
			LedLeft();
			WaitOnTimer0Match0();
		}
}
