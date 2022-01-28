
#include <array>
#include "asf.h"
#include "stdio_serial.h"
#include "conf_uart_serial.h"
#include "tasks.h"

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

static struct adc_module adc_instance;
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

uint32_t get_schedular_ticks_from_ms(uint32_t milli_seconds)
{
	return (milli_seconds * 20);
}

uint32_t get_schedular_ticks_from_us(uint32_t micro_seconds)
{
	return micro_seconds/50;
}

void init_app()
{
	system_init();
	configure_console();
	configure_adc();
	configure_tc();
	
	//Systick of 50us
	SysTick_Config(system_gclk_gen_get_hz(0)/20000);
	NVIC_EnableIRQ(SysTick_IRQn);		// Enable SysTick Interrupt
}

void toggle_led()
{
	port_pin_toggle_output_level(PIN_PA09);
}

static uint32_t filtered_adc_result {0};
void read_pot()
{
	static const size_t num_filter_samples {10};
	static std::array<uint16_t, num_filter_samples> adc_filter_samples;
	static size_t sample_count {0};
	uint16_t adc_result;

	adc_start_conversion(&adc_instance);
	while (adc_read(&adc_instance, &adc_result) == STATUS_BUSY);

	adc_filter_samples[sample_count++] = adc_result;
	if(sample_count >= num_filter_samples)
	{
		sample_count = 0;
		filtered_adc_result = 0;
		for(int idx = (num_filter_samples -1); idx >= 0; idx--)
		{
			filtered_adc_result += adc_filter_samples[idx];
		}
		filtered_adc_result = filtered_adc_result/num_filter_samples;
	}
}

void set_servo_position()
{
	uint32_t servo_position {(filtered_adc_result*100)/4095UL};

	//Upper Hysteresis
	servo_position = (servo_position > 95) ? 100 : servo_position;
	//Lower Hysteresis
	servo_position = (servo_position < 5) ? 0 : servo_position;

	uint32_t compare_value {(80 * servo_position) + 2000};

	tc_set_compare_value(&tc_instance, TC_COMPARE_CAPTURE_CHANNEL_0, compare_value);

	
	printf("TC Compare Value: %lu\r\n", compare_value);
	printf("Servo Position: %lu%%\r\n\r\n", servo_position);
}
