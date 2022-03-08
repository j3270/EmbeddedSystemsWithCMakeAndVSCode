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
#include <array>
#include "ISensor.h"

namespace Sensors {
    class LPS25 : public ISensor {

        public:

        static constexpr who_am_i {0xBD};

        enum class Registers : uint8_t
        {
            ref_p_xl = 0x08,  //rw
            ref_p_l,          //rw
            ref_p_h,          //rw
            who_am_i = 0x0F,  //r
            res_conf,         //rw
            ctrl1 = 0x20,     //rw
            ctrl2,            //rw
            ctrl3,            //rw
            ctrl4,            //rw
            interrupt_cfg,    //rw
            int_src,          //r
            status = 0x27,    //r
            press_out_xl,     //r
            press_out_l,      //r
            press_out_h,      //r
            temp_out_l,       //r
            temp_out_h,       //r
            fifo_ctrl = 0x2E, //rw
            fifo_status,      //r
            this_p_l,         //rw
            this_p_h,         //rw
            rpds_l = 0x39,    //rw
            rpds_h            //rw
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

        struct ControlConfig
        {
            union One
            {
                uint8_t whole;
                struct Fields
                {
                    uint8_t sim : 1;
                    uint8_t reset_az :1;
                    uint8_t bdu : 1;
                    uint8_t diff_en :1;
                    uint8_t odr : 3;
                    uint8_t pd : 1;
                }fields;
            }one;

            union Two
            {
                uint8_t whole;
                struct Fields
                {
                    uint8_t one_shot : 1;
                    uint8_t auto_zero : 1;
                    uint8_t sw_reset : 1;
                    uint8_t i2c_dis : 1;
                    uint8_t fifo_mean_dec : 1;
                    uint8_t stop_on_fth : 1;
                    uint8_t fifo_en : 1;
                    uint8_t boot : 1;
                }fields;
            }two;

            union Three
            {
                uint8_t whole;
                struct Fields
                {
                    uint8_t int_s1 : 1;
                    uint8_t int_s2 : 1;
                    uint8_t reserved : 4;
                    uint8_t pp_od : 1;
                    uint8_t int_h_l : 1;
                }fields;
            }three;

            union Four
            {
                uint8_t whole;
                struct Fields
                {
                    uint8_t drdy : 1;
                    uint8_t f_ovr : 1;
                    uint8_t f_fth : 1;
                    uint8_t f_empty : 1;
                    uint8_t reserved : 4;
                }fields;
            }four;
        };

        union InterruptConfig {
            uint8_t whole;
            struct Fields {
                uint8_t ph_e : 1;
                uint8_t pl_e : 1;
                uint8_t lir : 1;
                uint8_t reserved : 5;
            }fields;
        }
        
        union InterruptSource {
            uint8_t whole;
            struct Fields {
                uint8_t active : 1;
                uint8_t diff_pressure_low : 1;
                uint8_t diff_pressure_high : 1;
                uint8_t reserved : 5;
            }fields;
        };

        union Status {
            uint8_t whole;
            struct Fields {
                uint8_t temperature_data_available : 1;
                uint8_t pressure_data_available : 1;
                uint8_t reserved34 : 2;
                uint8_t temperature_over_run : 1;
                uint8_t pressure_over_run :1;
                uint8_t reserved67 : 2;
            }fields;
        };

        union FIFO_Config {
            uint8_t whole;
            struct Fields {
                uint8_t watermark : 5;
                uint8_t mode : 3;
            }fields;
        };

        union FIFO_Status {
            uint8_t whole;
            struct Fields {
                uint8_t data_level : 5;
                uint8_t empty : 1;
                uint8_t over_run : 1;
                uint8_t threshold : 1;
            }fields;
        };

        struct Config {
            ResolutionConfig res_config;
            ControlConfig ctrl_config;
            InterruptConfig int_config
            FIFO_Config fifo_config;
        };

        /**
         * @brief Construct a new LPS25 object
         * 
         */
        LPS25() = default;

        /**
         * @brief Get the default config object
         * 
         * @return Config 
         */
        Config get_default_config() final;

        /**
         * @brief 
         * 
         * @param config 
         * @param interface 
         * @param idx 
         */
        bool init(Config& config, Interface& interface, size_t idx) final;

        /**
         * @brief Get current pressure reading
         * 
         * @return float current pressure in Pa
         */
        float get_pressure() final;

        private:

        Config m_config;

        /**
         * @brief 
         * 
         * @param register 
         * @param data 
         */
        void write_register(Registers register, uint8_t data);

        /**
         * @brief 
         * 
         * @param register 
         * @return uint8_t 
         */
        uint8_t read_register(Registers register);

        /**
         * @brief 
         * 
         * @param start_register 
         * @param data 
         */
        void write_block(Registers start_register, std::array<uint8_t>& data);

        /**
         * @brief 
         * 
         * @param start_register 
         * @param data 
         */
        void read_block(Registers start_register, std::array<uint8_t>& data);
    };
}