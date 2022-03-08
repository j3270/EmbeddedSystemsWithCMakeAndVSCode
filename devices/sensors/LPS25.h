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
#include "IPressure.h"

namespace Sensors {

    class LPS25 : public IPressure {

        public:

        enum class Registers : uint8_t
        {
            ref_p_xl = 0x08,
            ref_p_l,
            ref_p_h,
            who_am_i = 0x0F,
            res_conf,
            ctrl1 = 0x20,
            ctrl2,
            ctrl3,
            ctrl4,
            interrupt_cfg,
            int_src,
            status = 0x27,
            press_out_xl,
            press_out_l,
            press_out_h,
            temp_out_l,
            temp_out_h,
            fifo_ctrl = 0x2E,
            fifo_status,
            this_p_l,
            this_p_h,
            rpds_l = 0x39,
            rpds_h
        };

        union ResolutionConfig
        {
            uint8_t whole;
            struct Fields
            {
                uint8_t avg_p : 2;
                uint8_t avg_t : 2;
                uint8_t reserved : 4;
            }fields;
        };
        

         /**
         * @brief Initialize the sensor with the given configuration
         * 
         * @param config Sensor configuration
         */
        void init(Config& config) final;

        /**
         * @brief Get current pressure reading
         * 
         * @return float current pressure in Pa
         */
        float get_pressure() final;
    };
}