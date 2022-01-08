
#include "asf.h"
#include "task_schedular.h"
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

void init_app()
{
	system_init();
	config_led();
	configure_adc();

	/* System timer configuration */
    SysTick_Config(SystemCoreClock / 1000000);
}

void main_task()
{
	static uint16_t adc_result {0};
	static uint32_t delay_time {0};

    port_pin_toggle_output_level(PIN_PA09);

	adc_start_conversion(&adc_instance);
	while (adc_read(&adc_instance, &adc_result) == STATUS_BUSY);
	//Scale 0 to 1000
	delay_time = (adc_result*1000)/4095;
	//Upper Hysteresis
	delay_time = (delay_time >= 950) ? 1000 : delay_time;
	//Lower Hysteresis
	delay_time = (delay_time <= 50) ? 0 : delay_time;
	//Print for debug
	SEGGER_RTT_printf(0, "Delay Time: %u\r\n", delay_time);
}