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

#include <cstdint>
#include "Manager.h"
#include "Task.h"

namespace Scheduler
{
    Manager::Manager(uint32_t (*get_ticks)(void)):
    get_ticks(get_ticks)
    {

    }

    void Manager::add_task(Task& task)
    {
        if(num_tasks < max_tasks)
        {
            tasks[num_tasks++] = &task;
        }
    }

    void Manager::run()
    {
        for(size_t idx {0}; idx < num_tasks; idx++)
        {
            uint32_t current_tick {get_ticks()};
            Task::Config& config {tasks[idx]->get_config()};

            if((current_tick - config.lastStartTick) >= config.interval)
            {
                tasks[idx]->run(current_tick);

                config.stopTick = get_ticks();
                config.executionTime = config.stopTick - config.startTick;

                // Check if execution time is greater than 50% of interval

                if(config.executionTime > (config.interval/2))
                {
                    //while(1); //Do something else, a fault or something provided by platform interface
                }
            }
        }
    }
} //namespace Scheduler