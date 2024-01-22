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

#include <cstdint>

/// Simple cooperative Scheduler
namespace Scheduler
{
/// Class for creating a task
class Task
{
public:

    /// Configuration of task
    struct Config
    {
        uint32_t startTick;
        uint32_t stopTick;
        uint32_t lastStartTick;
        uint32_t executionTime;
        uint32_t interval;
        void(*execute)();
    };

    /// Status of task
    enum class Status
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
    * @param[in] interval - interval at which task should be run in
    * terms of Scheduler ticks
    * @param[in] execute - pointer to function implementing task
    */
    Task(uint32_t interval, void(*execute)());

    /**
    * @brief Gets task configuration
    *
    * @return configuration of task
    */
    Config& get_config();

    /**
    * @brief Runs task execute function
    *
    * @param[in] start_tick - Scheduler tick at which task was started
    *
    * @return status of task
    */
    Status run(uint32_t start_tick);

private:
    Config config;
};
}//namespace Scheduler