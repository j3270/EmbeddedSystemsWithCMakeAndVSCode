
#include "asf.h"

int main(void)
{
	system_init();
	delay_init();

	while (true) 
	{
		 delay_ms(500);
		 LED_Toggle(LED_0_PIN);
	}
}

