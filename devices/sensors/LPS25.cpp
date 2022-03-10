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

#include "LPS25.h"

namespace Sensors {
    
    bool LPS25::init(Sensors::Interface& interface, size_t idx)
    {
        bool initialized {false};
        m_interface = interface;

        switch(m_interface)
        {
            case Sensors::Interface::I2C:
                //initialized = get_i2c_bus(idx, serial);
            break;

            case Sensors::Interface::SPI:
                //initialized = get_spi_bus(idx, serial);
            break;

            default:
                initialized = false;
            break;
        }

        return initialized;
    }
    
    float LPS25::get_data()
    {
        return 0.0f;
    }

    LPS25::Config get_default_config()
    {
        LPS25::Config config;

        return config;
    }

    void LPS25::set_config(LPS25::Config& config)
    {
        m_config = config;
    }

    void LPS25::write_register(Registers register, uint8_t data)
    {
        if(m_interface == Sensors::Interface::I2C)
        {

        }
        else
        {

        }
    }

    uint8_t LPS25::read_register(Registers register)
    {
        if(m_interface == Sensors::Interface::I2C)
        {

        }
        else
        {
            
        }

        return 0;
    }

    void LPS25::write_block(Registers start_register, uint8_t * data)
    {
        if(m_interface == Sensors::Interface::I2C)
        {

        }
        else
        {
            
        }
    }

    void LPS25::read_block(Registers start_register, uint8_t * data)
    {
        if(m_interface == Sensors::Interface::I2C)
        {

        }
        else
        {
            
        }
    }
}