
#include "asf.h"

int main(void)
{
	system_init();
	delay_init();

	bool button_pressed {false};

	while (true) 
	{
		button_pressed = !port_pin_get_input_level(BUTTON_0_PIN);
		button_pressed ? delay_ms(125) : delay_ms(500);
		port_pin_toggle_output_level(LED_0_PIN);
	}
}

