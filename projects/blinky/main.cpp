
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

int main(void)
{
	system_init();
	delay_init();
	config_led();

	while (true) 
	{
		delay_ms(500);
		port_pin_toggle_output_level(PIN_PA09);
	}
}

