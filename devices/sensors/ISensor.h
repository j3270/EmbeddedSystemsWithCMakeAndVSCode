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
#include <cstdlib>

namespace Sensors {

    /**
     * @brief Type of sensor; analog or digital
     * 
     */
    enum class Interface
    {
        Analog = 0,
        SPI,
        I2C,
        UART
    };

    /**
     * @brief Interface class for a sensor
     * 
     */
    class ISensor {
        
        public:

        /**
         * @brief 
         * 
         * @param config 
         * @param interface 
         * @param idx 
         */
        virtual bool init(Interface& interface, size_t idx) = 0;

        /**
         * @brief Get the data object
         * 
         * @return float 
         */
        virtual float get_data() = 0;

        /**
         * @brief Destroy the ISensor object
         * 
         */
        virtual ~ISensor(){}
    };
}