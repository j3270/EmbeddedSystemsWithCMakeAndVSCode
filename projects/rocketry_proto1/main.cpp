
#include "asf.h"
#include "stdio_serial.h"

int main(void)
{
	system_init();
	delay_init();

	printf("Hello World!\r\n");

	uint32_t battery_voltage {get_battery_voltage_x100()};

	while (true) 
	{
		LED_Toggle(LED_0_PIN);
		delay_ms(500);
		battery_voltage = get_battery_voltage_x100();
		printf("Battery Voltage: %lu\r\n", battery_voltage);	
	}
}

