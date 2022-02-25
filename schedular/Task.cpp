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
#include "Task.h"

namespace Schedular
{
    Task::Task(std::string& name, uint32_t interval, void(*execute)()):
    name(name)
    {
        config.startTick = 0;
        config.stopTick = 0;
        config.lastStartTick = 0;
        config.executionTime = 0;
        config.interval = interval;
        config.execute = execute;
    }


    Task::Task(const char * name, uint32_t interval, void(*execute)()):
    name(name)
    {
        config.startTick = 0;
        config.stopTick = 0;
        config.lastStartTick = 0;
        config.executionTime = 0;
        config.interval = interval;
        config.execute = execute;
    }

    Task::Config& Task::get_config()
    {
        return config;
    }

    Task::Status Task::run(uint32_t start_tick)
    {
        Task::Status status {Status::running};
        config.startTick = start_tick;

        //Check if task failed to start on time
        if(config.startTick - config.lastStartTick > config.interval)
        {
            status = Status::late_start;
            //while(1); //Do something else, a fault or something provided by platform interface
        }
        config.lastStartTick = config.startTick;

        config.execute();

        return status;
    }
}//namespace Schedular