/******************************************************************************
 *  Copyright (c)
 *  Curtis Instruments, Inc.
 *
 *  Developed at Curtis PMC
 *  235 E. Airway Blvd.
 *  Livermore,  CA  94551
 *  (925) 961-1088
 *
 ******************************************************************************/

#pragma once

#include <string>
#include <cstddef>
#include <cstdint>

/// Simple cooperative schedular
namespace CoOpSchedular
{
	
	/// Maximum number of tasks
    static constexpr size_t MaxTasks {16};
	/// Maximum length of task name
    static constexpr uint32_t MaxTaskNameLength {32};

    /// Class for creating a task	
    class Task
    {
        public:
            
			/// Configuration of task
            struct TaskConfig
            {
                uint32_t startTick;
                uint32_t stopTick;
                uint32_t lastStartTick;
                uint32_t executionTime;
                uint32_t interval;
                void(*execute)(); 
            };
            
			/// Status of task
            enum class TaskStatus
            {
                idle = 0,
                running,
                late_start,
                exceeded_runtime
            };
            
			/**
			* @brief Default constructor
			*/
            Task() = default;
            
			/**
			* @brief Task constructor
			*
			* @param[in] name - sting object name of task
			* @param[in] interval - interval at which task should be run in 
			* terms of schedular ticks
			* @param[in] execute - pointer to function implementing task
			*/
            Task(std::string& name, uint32_t interval, void(*execute)());
            
			/**
			* @brief Task constructor
			*
			* @param[in] name - C string name of task
			* @param[in] interval - interval at which task should be run in 
			* terms of schedular ticks
			* @param[in] execute - pointer to function implementing task
			*/
            Task(const char *  name, uint32_t interval, void(*execute)());
            
			/**
			* @brief Gets task configuration
			*
			* @return configuration of task
			*/
            TaskConfig& get_config();
            
			/**
			* @brief Runs task execute function
			*
			* @param[in] start_tick - schedular tick at which task was started
			*
			* @return status of task
			*/
            TaskStatus run(uint32_t start_tick);
            
        private:
            std::string name;
            TaskConfig task_config;
    };
    
	/// Class for scheduling tasks
    class TaskSchedular
    {
        public:
            
			/**
			* @brief TaskSchedular default constructor
			*/
            TaskSchedular() = default;
            
			/**
			* @brief Adds task to schedular
			*
			* @param[in] task - task to add
			*
			* @return none*/
            void add_task(Task& task);
            
			/**
			* @brief Runs schedular
			*/
            void run();
            
        private:
            
            size_t num_tasks {0};
            Task tasks[MaxTasks];
    };

}; //namespace CoOpSchedular