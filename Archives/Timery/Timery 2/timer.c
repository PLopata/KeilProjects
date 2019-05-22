#include <LPC21xx.H>
#include "timer.h"

#define T0TC_ON_bm 1 
#define T0TC_RESET_bm (1 << 1)
#define RESET_ON_MR0_bm (1<<1)
#define INTERRUPT_ON_MR0_bm 1

void InitTimer0(void)
{
	T0TCR = T0TC_ON_bm;                                   //wlaczenie timer countera za pomoca T0TCR
}

void WaitOnTimer0( unsigned int uiTime )
{
	unsigned char ucMicrosecondsConverter = 0xF;
	
	T0TCR = T0TC_RESET_bm; 		                            //zresetowanie rejestru timer counter
	T0TCR = T0TC_ON_bm;                                   //wlaczenie timer countera
	while ( T0TC < (ucMicrosecondsConverter*uiTime) ) {} //oczekiwanie az T0TC zrowna sie z wartoscia podana do funckji 
}

void InitTimer0Match0( unsigned int uiDelayTime )
{
	unsigned char ucMicrosecondsConverter = 0xF;
	
	T0MR0 = ucMicrosecondsConverter*uiDelayTime;          //ustawienie match registera
	T0MCR = (RESET_ON_MR0_bm | INTERRUPT_ON_MR0_bm);      //ustaw: dla T0TC==T0MR0 zresetuj T0TC i ustaw flage przerwania na rejestrze T0IR
	T0TCR = T0TC_RESET_bm;                                //zresetowanie rejestru timer counter
	T0TCR = T0TC_ON_bm;                                   //wlaczenie timer countera
}

void WaitOnTimer0Match0()
{
	while ( (T0IR & INTERRUPT_ON_MR0_bm) == 0) {}         //oczekiwanie na przerwanie
	T0IR = INTERRUPT_ON_MR0_bm;                  //wyzerowanie flagi przerwania
}
