
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

/* Number of times to try to send packet if failed. */
#define TIMEOUT 1000

struct i2c_master_module i2c_master_instance;

void configure_i2c_master(void)
{
	/* Initialize config structure and software module. */
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	
	/* Change buffer timeout to something longer. */
	config_i2c_master.buffer_timeout = 10000;

	/* Initialize and enable device with config. */
	i2c_master_init(&i2c_master_instance, SERCOM2, &config_i2c_master);

	i2c_master_enable(&i2c_master_instance);
	
}

int main(void)
{
	system_init();
	delay_init();
	configure_console();
	configure_i2c_master();

	printf("Hello World!\r\n");

	i2c_master_packet test_packet;
	test_packet.data_length = 0;
	test_packet.ten_bit_address = false;
	test_packet.high_speed = false;

	for(uint8_t adrs = 0; adrs < 0x80; adrs++)
	{
		printf("Trying slave address %d\r\n", adrs);
		test_packet.address = adrs;
		status_code i2c_status = i2c_master_write_packet_wait(&i2c_master_instance, &test_packet);
		if(i2c_status == STATUS_OK)
		{
			printf("Found device at %d\r\n", adrs);
		}
		LED_Toggle(LED_0_PIN);
		delay_ms(100);
	}

	while (true);
}

