
#include "asf.h"

/** Configure LED0, turn it off*/
static void config_led(void)
{
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA09, &pin_conf);
	port_pin_set_output_level(PIN_PA09, false);
}

/** Configure PB1, active low*/
static void config_push_button(void)
{
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	pin_conf.direction  = PORT_PIN_DIR_INPUT;
	port_pin_set_config(PIN_PA07, &pin_conf);
}

int main(void)
{
	system_init();
	delay_init();
	config_led();
	config_push_button();

	bool button_pressed {false};

	while (true) 
	{
		button_pressed = !port_pin_get_input_level(PIN_PA07);
		button_pressed ? delay_ms(100) : delay_ms(500);
		port_pin_toggle_output_level(PIN_PA09);
	}
}

