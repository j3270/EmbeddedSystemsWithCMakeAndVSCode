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

#include <array>
#include <cstdint>
#include "bsp.h"
#include "tasks.h"


static uint32_t filtered_adc_result {0};
void read_pot()
{
	static const size_t num_filter_samples {10};
	static std::array<uint16_t, num_filter_samples> adc_filter_samples;
	static size_t sample_count {0};
	uint16_t adc_result;

	adc_start_conversion(BSP::get_pot_adc());
	while (adc_read(BSP::get_pot_adc(), &adc_result) == STATUS_BUSY);

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

static uint32_t servo_position {0};
static uint32_t compare_value {0};
void set_servo_position()
{
	servo_position = (filtered_adc_result*100)/4095UL;
	//Upper Hysteresis
	servo_position = (servo_position > 95) ? 100 : servo_position;
	//Lower Hysteresis
	servo_position = (servo_position < 5) ? 0 : servo_position;

	compare_value = (80 * servo_position) + 2000;

	tc_set_compare_value(BSP::get_servo_tmr(), TC_COMPARE_CAPTURE_CHANNEL_0, compare_value);
}

void display_data()
{
	printf("Filtered ADC result: %lu\r\n", filtered_adc_result);
	printf("TC Compare Value: %lu\r\n", compare_value);
	printf("Servo Position: %lu%%\r\n\r\n", servo_position);
}
