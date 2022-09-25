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

#include "bsp.h"
#include "stdio_serial.h"
#include "conf_uart_serial.h"


volatile static uint32_t systick_ticks = 0;
#ifdef __cplusplus
  extern "C" {
#endif
void SysTick_Handler(void)
{
    systick_ticks++;
}
#ifdef __cplusplus
}
#endif

namespace BSP {

	uint32_t get_sys_ticks()
	{
	    return systick_ticks;
	}

	static struct usart_module cdc_uart_module;
	struct usart_module * get_console_uart()
	{
		return &cdc_uart_module;
	}

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

	static struct adc_module adc_instance;
	struct adc_module * get_pot_adc()
	{
		return &adc_instance;
	}

	static void configure_adc(void)
	{
		struct adc_config config_adc;
		adc_get_config_defaults(&config_adc);
		config_adc.reference = ADC_REFERENCE_INTVCC1; //1.65V
		config_adc.positive_input = ADC_POSITIVE_INPUT_PIN8;
		adc_init(&adc_instance, ADC, &config_adc);
		adc_enable(&adc_instance);
	}

	static struct tc_module tc_instance;
	struct tc_module * get_servo_tmr()
	{
		return &tc_instance;
	}

	static void configure_tc(void)
	{

		struct tc_config config_tc;

		tc_get_config_defaults(&config_tc);

		config_tc.counter_size    = TC_COUNTER_SIZE_16BIT;
		config_tc.wave_generation = TC_WAVE_GENERATION_NORMAL_PWM;
		config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV2;

		config_tc.pwm_channel[0].enabled = true;
		config_tc.pwm_channel[0].pin_out = PIN_PB02E_TC6_WO0;
		config_tc.pwm_channel[0].pin_mux = MUX_PB02E_TC6_WO0;

		tc_init(&tc_instance, TC6, &config_tc);
		tc_enable(&tc_instance);
	}

	void init(uint32_t sys_tick_freq_hz, bool enable_sys_tick)
	{
		system_init();
		configure_console();
		configure_adc();
		configure_tc();

		if(enable_sys_tick)
		{
			const uint32_t cpu_frequency_hz = system_cpu_clock_get_hz();
			const uint32_t cpu_ticks_per_sys_tick = cpu_frequency_hz/sys_tick_freq_hz;
			if(SysTick_Config(cpu_ticks_per_sys_tick) != 0)
			{
				while(1); //Failed to setup systick
			}
			NVIC_EnableIRQ(SysTick_IRQn); // Enable SysTick Interrupt
		}
	}

	void set_led0()
	{
		port_pin_set_output_level(LED0_PIN, true);
	}

	void clr_led0()
	{
		port_pin_set_output_level(LED0_PIN, false);
	}

	void toggle_led0()
	{
		port_pin_toggle_output_level(LED0_PIN);
	}
}