
#include <array>
#include "asf.h"
#include "tasks.h"
#include "SEGGER_RTT.h"

/** Configure LED0, turn it off*/
static void config_led(void)
{
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PIN_PA09, &pin_conf);
	port_pin_set_output_level(PIN_PA09, false);
}

static struct adc_module adc_instance;
static void configure_adc(void)
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
	config_adc.reference = ADC_REFERENCE_INTVCC1; //1.65V
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
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
	config_led();
	configure_adc();
	
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

	SEGGER_RTT_printf(0, "Servo Position: %u%%\r\n", servo_position);
}
