
#include "asf.h"
#include "stdio_serial.h"
#include "conf_uart_serial.h"

static struct usart_module cdc_uart_module;
static void configure_console(void)
{
	struct usart_config usart_conf;

	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART_MODULE, &usart_conf);
	usart_enable(&cdc_uart_module);
}

int main(void)
{
	system_init();
	delay_init();
	configure_console();

	printf("Hello World!\r\n");

	uint8_t my_char {0};

	while (true) 
	{
		usart_serial_getchar(&cdc_uart_module, &my_char);
		usart_serial_putchar(&cdc_uart_module, my_char);

		port_pin_toggle_output_level(LED_0_PIN);
		delay_ms(100);
		port_pin_toggle_output_level(LED_0_PIN);
	}
}

