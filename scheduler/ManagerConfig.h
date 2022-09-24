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

//#include "platform.h" //Your system header

/// Simple cooperative Scheduler
namespace Scheduler
{
    // Define system fn for getting system ticks
    constexpr uint32_t (*get_scheduler_ticks)() {micros};

    // Define time in terms of get_system_ticks
    constexpr uint32_t fifty_micro_seconds {50};
    constexpr uint32_t hundred_micro_seconds {fifty_micro_seconds * 2};
    constexpr uint32_t one_milli_second {hundred_micro_seconds * 10};
    constexpr uint32_t ten_milli_second {one_milli_second * 10};
    constexpr uint32_t hundred_milli_second{ten_milli_second * 10};
    constexpr uint32_t one_second {hundred_milli_second * 10};
}; //namespace Scheduler
