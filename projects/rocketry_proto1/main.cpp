
#include "asf.h"
#include "stdio_serial.h"

int main(void)
{
	system_init();
	delay_init();

	printf("Hello World!\r\n");

	uint8_t my_char {0};

	while (true) 
	{
		usart_serial_getchar(get_console_usart(), &my_char);
		usart_serial_putchar(get_console_usart(), my_char);

		LED_Toggle(LED_0_PIN);
		delay_ms(100);
		LED_Toggle(LED_0_PIN);
	}
}

