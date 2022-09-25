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
#include "ManagerConfig.h"

int main(void)
{
    constexpr uint32_t Four_Hz {4};
    constexpr uint32_t Ten_Hz {10};
    constexpr uint32_t Seventy_Hz {70};
    constexpr uint32_t Two_Hundred_Hz {200};
    constexpr uint32_t One_Hundred_KHz {100000};


    BSP::init(One_Hundred_KHz);

	// Create task scheduler and add tasks
    Scheduler::Manager scheduler(BSP::get_sys_ticks);

    // Setup application task main_task
    Scheduler::Task task1(Scheduler::tics_from_frequency(Ten_Hz), BSP::toggle_led0);
    scheduler.add_task(&task1);

    Scheduler::Task task2(Scheduler::tics_from_frequency(Two_Hundred_Hz), read_pot);
    scheduler.add_task(&task2);

    Scheduler::Task task3(Scheduler::tics_from_frequency(Seventy_Hz), set_servo_position);
    scheduler.add_task(&task3);

    Scheduler::Task task4(Scheduler::tics_from_frequency(Four_Hz), display_data);
    scheduler.add_task(&task4);

    while(1)
    {
        scheduler.run();
    } 
}
