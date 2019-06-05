#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"

#define DETECTOR_bm (1<<10)

void DetectorInit()
{
	IO0DIR = ( IO0DIR & (~DETECTOR_bm) );
}

enum DetectorState {INACTIVE, ACTIVE};

enum DetectorState eReadDetector()
{
	if ( (IO0PIN & DETECTOR_bm) == 0)
	{
		return ACTIVE;
	}
	else 
	{
		return INACTIVE;
	}
}


enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo
{
	enum ServoState     eState;
	unsigned int        uiCurrentPosition;
	unsigned int        uiDesiredPosition;
};

struct Servo sServo;


void Automat(void)
{
	switch(sServo.eState)
	{	
		case CALLIB:
		{
			if ( eReadDetector() == INACTIVE )
			{
				sServo.eState = CALLIB;
				LedStepLeft();
			}
			else 
			{
				sServo.uiDesiredPosition=0;
				sServo.uiCurrentPosition=0;
				sServo.eState = IDLE;
			}
			break;
		}
		
		case IDLE:
		{
			if ( sServo.uiCurrentPosition != sServo.uiDesiredPosition )
			{
				sServo.eState = IN_PROGRESS;
			}
			else
			{
				sServo.eState = IDLE;
			}
			break;
		}
		
		case IN_PROGRESS:
		{
			if ( sServo.uiCurrentPosition != sServo.uiDesiredPosition )
			{
				if ( sServo.uiCurrentPosition < sServo.uiDesiredPosition )
				{
					LedStepRight();
					sServo.uiCurrentPosition++;
				}
				else 
				{
					LedStepLeft();
					sServo.uiCurrentPosition--;
				}
				sServo.eState = IN_PROGRESS;
			}
			else
			{
				sServo.eState = IDLE;
			}
			break;
		}
	}
}

int main ()
{
	LedInit();
	DetectorInit();
	Timer0Interrupts_Init(40000, &Automat );

	while(1)
	{
		enum KeyboardState eKeyboard = eReadButton();
		
		switch (eKeyboard)
		{
			case BUTTON_0:
			{
				sServo.eState = CALLIB;
				break;
			}
			case BUTTON_1:
			{
				sServo.uiDesiredPosition = 12;
				break;
			}
			case BUTTON_2:
			{
				sServo.uiDesiredPosition = 24;
				break;
			}
			case BUTTON_3:
			{
				sServo.uiDesiredPosition = 36;
				break;
			}
			default:
			{
				break;
			}
		}
	}
}
