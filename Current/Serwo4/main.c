#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include "servo.h"

int main ()
{
	ServoInit(100000);
	while(1)
	{
		enum KeyboardState eKeyboard = eReadButton();
		
		switch (eKeyboard)
		{
			case BUTTON_0:
			{
				ServoCallib();
				break;
			}
			case BUTTON_1:
			{
				ServoGoTo(12);
				break;
			}
			case BUTTON_2:
			{
				ServoGoTo(24);
				break;
			}
			case BUTTON_3:
			{
				ServoGoTo(36);
				break;
			}
			default:
			{
				break;
			}
		}
	}
}
