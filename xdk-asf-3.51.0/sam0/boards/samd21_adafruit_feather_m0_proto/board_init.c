/******************************************************************************
* MIT License
* 
* Copyright (c) 2021 Justin J. Jordan
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
******************************************************************************/

#include "compiler.h"
#include "adc.h"
#include "board.h"
#include "conf_board.h"
#include "port.h"
#include "stdio_serial.h"

#if defined(__GNUC__)
void board_init(void) WEAK __attribute__((alias("system_board_init")));
#elif defined(__ICCARM__)
void board_init(void);
#  pragma weak board_init=system_board_init
#endif

static struct usart_module console_usart_module;
static void configure_console_uart(void)
{
	struct usart_config usart_conf;

	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&console_usart_module, CONF_STDIO_USART_MODULE, &usart_conf);
	usart_enable(&console_usart_module);
}

struct usart_module* get_console_usart()
{
	return &console_usart_module;
}

static struct adc_module adc_instance;
static void configure_adc(void)
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	config_adc.reference = ADC_REFERENCE_INTVCC0; //3.3/1.48 ~ 2.2297V
	config_adc.positive_input = ADC_POSITIVE_INPUT_PIN7;
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}

uint32_t get_battery_voltage_x100()
{
	const float ADC_REF = 3.3F/1.48F;
	const float ARD_RES = 4096.0F;

	uint16_t adc_result;

	adc_start_conversion(&adc_instance);
	while (adc_read(&adc_instance, &adc_result) == STATUS_BUSY);

	float adc_result_x2 = adc_result * 2.0; //We divided battery voltage by two 
	float battery_voltage = ADC_REF/ARD_RES * adc_result_x2;

	uint32_t battery_voltage_x100 = (uint32_t) (battery_voltage * 100);

	return battery_voltage_x100;
}


void system_board_init(void)
{
    struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	/* Configure LED as output, turn it off */
	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_0_PIN, &pin_conf);
	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);

	configure_console_uart();
	configure_adc();
}