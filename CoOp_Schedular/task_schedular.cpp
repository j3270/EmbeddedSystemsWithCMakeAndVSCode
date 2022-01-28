
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