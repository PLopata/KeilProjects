#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

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

void ServoInit(unsigned int uiServoFrequency)
{
	unsigned int uiTimePeriod;
	
	uiTimePeriod = 1000000/uiServoFrequency;
	DetectorInit();
	LedInit();
	Timer0Interrupts_Init((uiTimePeriod), &Automat );
	ServoCallib();
}

void ServoCallib()
{
	sServo.eState = CALLIB;
	while ( sServo.eState != IDLE ) {} 
}

void ServoGoTo( unsigned int uiPosition )
{
	sServo.uiDesiredPosition = uiPosition;
	while ( sServo.eState != IDLE ){}
}
