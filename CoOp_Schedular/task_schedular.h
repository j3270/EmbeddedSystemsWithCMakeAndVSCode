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

#pragma once

#include <string>
#include <cstddef>
#include <cstdint>

/// Simple cooperative schedular
namespace CoOpSchedular
{
	uint32_t get_schedular_ticks();
	
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