
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

static struct usart_module cdc_uart_module;
static void configure_console(void)
{
	struct usart_config usart_conf;

	//8N1 9600 PA05 is Rx and PA08 is Tx on SAMD10C14
	//8N1 9600 PA05 is Rx and PA06 is Tx on SAMD21G15B
	usart_get_config_defaults(&usart_conf);
	usart_serial_init(&cdc_uart_module, SERCOM0, &usart_conf);
	usart_enable(&cdc_uart_module);
}

static struct adc_module adc_instance;
static void configure_adc(void)
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}

int main(void)
{
	system_init();
	delay_init();
	configure_console();
	config_led();
	configure_adc();

	const uint8_t hellow_world[] = "Hello World\r\n";
	size_t hello_world_len = sizeof(hellow_world)/sizeof(hellow_world[0]);
	usart_serial_write_packet(&cdc_uart_module, hellow_world, hello_world_len);

	while (true) 
	{
		delay_ms(100);
		port_pin_toggle_output_level(PIN_PA09);
	}
}