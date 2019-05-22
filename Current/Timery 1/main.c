#include "led.h"
#include "keyboard.h"
#include "timer.h"

int main()
{
	LedInit();
	KeyboardInit();
	InitTimer0();
	while(1)
		{
			LedLeft();
			WaitOnTimer0(1);
		}
		/* git test 1 */
		/* test git */
}
