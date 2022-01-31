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

#include <string>
#include <cstddef>
#include <cstdint>
#include "task_schedular.h"

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

namespace CoOpSchedular
{
    uint32_t get_schedular_ticks()
    {
        return systick_ticks;
    }
	/**** Class Task Defenitions **********************************************/
    Task::Task(std::string & name, uint32_t interval, void(*execute)())
    {
        task_config.startTick = 0;
        task_config.stopTick = 0;
        task_config.lastStartTick = 0;
        task_config.executionTime = 0;
        task_config.interval = interval;
        task_config.execute = execute;
        this->name = name;
    }
    
    
    Task::Task(const char * name, uint32_t interval, void(*execute)())
    {
        task_config.startTick = 0;
        task_config.stopTick = 0;
        task_config.lastStartTick = 0;
        task_config.executionTime = 0;
        task_config.interval = interval;
        task_config.execute = execute;
        this->name = name;
    }
            
    Task::TaskConfig& Task::get_config()
    {
        return task_config;
    }
            
    Task::TaskStatus Task::run(uint32_t start_tick)
    {
        Task::TaskStatus status {TaskStatus::running};
        task_config.startTick = start_tick;
                    
        //Check if task failed to start on time
        if(task_config.startTick - task_config.lastStartTick > task_config.interval)
        {
            status = TaskStatus::late_start;
            //while(1); //Do something else, a fault or something provided by platform interface
        }
        task_config.lastStartTick = task_config.startTick;
        
        task_config.execute();
        
        return status;
    }
	/**** End of Class Task Defenitions ***************************************/
    
    
	/**** Class TaskSchedular Defenitions *************************************/
    void TaskSchedular::add_task(Task & task)
    {
        if(num_tasks < MaxTasks)
        {
            tasks[num_tasks++] = task;
        }
    }
            
    void TaskSchedular::run()
    {
        for(size_t idx {0}; idx < num_tasks; idx++)
        {
            uint32_t current_tick {systick_ticks};
            Task::TaskConfig& config {tasks[idx].get_config()};
            
            if((current_tick - config.lastStartTick) >= config.interval)
            {   
                tasks[idx].run(current_tick);
                
                config.stopTick = systick_ticks;
                config.executionTime = config.stopTick - config.startTick;
                
                // Check if execution time is greater than 50% of interval
               
                if(config.executionTime > (config.interval/2))
                {
                    //while(1); //Do something else, a fault or something provided by platform interface
                }
            }
        }
    }
	/**** End of Class TaskSchedular Defenitions ******************************/
	
} //namespace CoOpSchedular