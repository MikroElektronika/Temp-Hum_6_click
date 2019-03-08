/*
    __temphum6_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__temphum6_driver.h"
#include "__temphum6_hal.c"

/* ------------------------------------------------------------------- MACROS */

/* Chip constants */
const uint16_t _TEMPHUM6_PART_ID = 0x0210;
const uint8_t _TEMPHUM6_DEVICE_SLAVE_ADDRESS = 0x43;

/* Registers */
const uint8_t _TEMPHUM6_REG_PART_ID              = 0x00;
const uint8_t _TEMPHUM6_REG_UNIQUE_IDENTIFIER    = 0x04;
const uint8_t _TEMPHUM6_REG_SYSTEM_CONTROL       = 0x10;
const uint8_t _TEMPHUM6_REG_SYSTEM_STATUS        = 0x11;
const uint8_t _TEMPHUM6_REG_SENS_RUN             = 0x21;
const uint8_t _TEMPHUM6_REG_SENS_START           = 0x22;
const uint8_t _TEMPHUM6_REG_SENS_STOP            = 0x23;
const uint8_t _TEMPHUM6_REG_SENS_STATUS          = 0x24;
const uint8_t _TEMPHUM6_REG_TEMPERATURE          = 0x30;
const uint8_t _TEMPHUM6_REG_RELATIVE_HUMIDITY    = 0x33;

/* Status */
const uint8_t _TEMPHUM6_STATUS_I2C_ERROR = 4;
const uint8_t _TEMPHUM6_STATUS_CRC_ERROR = 3;
const uint8_t _TEMPHUM6_STATUS_INVALID = 2;
const uint8_t _TEMPHUM6_STATUS_OK = 1;

/* Temperature data in ...*/
const uint8_t _TEMPHUM6_TEMP_IN_FAHRENHEIT = 2;
const uint8_t _TEMPHUM6_TEMP_IN_KELVIN     = 1;
const uint8_t _TEMPHUM6_TEMP_IN_CELSIUS    = 0;

/* Controls the system */
const uint8_t _TEMPHUM6_LOW_POWER_DISABLE = 0x00;
const uint8_t _TEMPHUM6_LOW_POWER_ENABLE  = 0x01;

/* System status */
const uint8_t _TEMPHUM6_SYSTEM_IS_IN_STANDBY_OR_BOOTING_STATE = 0;
const uint8_t _TEMPHUM6_SYSTEM_IS_IN_ACTIVE_STATE             = 1;

/* Register configures the run modes */
const uint8_t _TEMPHUM6_HUM_RUN_SINGLE_SHOT_MODE  = 0x00;
const uint8_t _TEMPHUM6_TEMP_RUN_SINGLE_SHOT_MODE = 0x00;
const uint8_t _TEMPHUM6_HUM_RUN_CONTINUOUS_MODE   = 0x02;
const uint8_t _TEMPHUM6_TEMP_RUN_CONTINUOUS_MODE  = 0x01;

/* Starts a measurement for the sensors */
const uint8_t _TEMPHUM6_HUM_START_MEASUREMENT  = 0x02;
const uint8_t _TEMPHUM6_TEMP_START_MEASUREMENT = 0x01;
const uint8_t _TEMPHUM6_DISABLE_MEASUREMENT    = 0x00;

/* Stops a continuous measurement */
const uint8_t _TEMPHUM6_HUM_STOP_CONTINUOUS_MEASUREMENT  = 0x02;
const uint8_t _TEMPHUM6_TEMP_STOP_CONTINUOUS_MEASUREMENT = 0x01;
const uint8_t _TEMPHUM6_DISABLE_CONTINUOUS_MEASUREMENT   = 0x00;

/* ---------------------------------------------------------------- VARIABLES */

/* CRC const */
static const uint8_t _CRC7WIDTH = 7;
static const uint8_t _CRC7POLY = 0x89;
static const uint8_t _CRC7IVEC = 0x7F;
/* Payload data  */
static const uint8_t  _DATA7WIDTH = 17;
static const uint32_t _DATA7MASK = ((1UL << _DATA7WIDTH) -1 );
static const uint32_t _DATA7MSB = (1UL<<(_DATA7WIDTH -1));

#ifdef   __TEMPHUM6_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint32_t _CRC7( uint32_t val );

static void BOOTING_TIME();
static void SINGLE_TIME();
static void COUNT_TIME();

static void _extract(uint32_t val, uint16_t *_data, uint8_t *status);

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static uint32_t _CRC7( uint32_t val ) 
{
    uint32_t _bit;
    // Setup polynomial
    uint32_t pol = _CRC7POLY;
    // Align polynomial with data
    pol = pol << ( _DATA7WIDTH - _CRC7WIDTH -1 );
    // Loop variable (indicates which bit to test, start with highest)
    _bit = _DATA7MSB;
    // Make room for CRC value
    val = val << _CRC7WIDTH;
    _bit = _bit << _CRC7WIDTH;
    pol = pol << _CRC7WIDTH;
    // Insert initial vector
    val |= _CRC7IVEC;
    // Apply division until all bits done
    while( _bit & (_DATA7MASK << _CRC7WIDTH) ) 
    {
        if( _bit & val ) 
        { 
            val ^= pol;
        }
        _bit >>= 1;
        pol >>= 1;
    }
    return val;
}
static void BOOTING_TIME()
{
    Delay_1ms();
    Delay_1ms();
    Delay_1ms();
}

static void SINGLE_TIME()
{
    Delay_100ms();
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
}

static void COUNT_TIME()
{
    Delay_100ms();   
    Delay_100ms();
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
}

static void _extract(uint32_t val, uint16_t *_data, uint8_t *status)
{
    uint8_t  valid;
    uint32_t crc;
    uint32_t payload;
    uint8_t  crc_ok;

    * _data = (val>>0 ) & 0xffff;
    valid   = (val>>16) & 0x1;
    crc     = (val>>17) & 0x7f;
    payload = (val>>0 ) & 0x1ffff;

    if(_CRC7(payload) == crc)
    {
        crc_ok = 1;
    }
    else
    {
        crc_ok = 0;
    }

    if( crc_ok != 1 )
    {
        *status = _TEMPHUM6_STATUS_CRC_ERROR;
    }
    else if( valid != 1 )
    {
        *status= _TEMPHUM6_STATUS_INVALID;
    }
    else
    {
        *status= _TEMPHUM6_STATUS_OK;
    }
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __TEMPHUM6_DRV_SPI__

void temphum6_spiDriverInit(T_TEMPHUM6_P gpioObj, T_TEMPHUM6_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __TEMPHUM6_DRV_I2C__

void temphum6_i2cDriverInit(T_TEMPHUM6_P gpioObj, T_TEMPHUM6_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __TEMPHUM6_DRV_UART__

void temphum6_uartDriverInit(T_TEMPHUM6_P gpioObj, T_TEMPHUM6_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

void temphum6_writeData(uint8_t reg, uint8_t *InData, uint8_t nData)
{
    uint8_t writeReg[ 50 ];
    uint8_t cnt;
    
    writeReg[ 0 ] = reg;

    for(cnt = 0; cnt < nData; cnt++)
    {
        writeReg[cnt + 1] = InData[ cnt ];
    }
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeReg, nData + 1, END_MODE_STOP);
}

void temphum6_writeByte(uint8_t reg, uint8_t _data)
{
    uint8_t writeReg[ 2 ];
    
    writeReg[ 0 ] = reg;
    writeReg[ 1 ] = _data;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeReg, 2, END_MODE_STOP);
}

void temphum6_readData(uint8_t reg, uint8_t *outData, uint8_t nData)
{
    uint8_t writeReg[ 1 ];
    
    writeReg[ 0 ] = reg;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeReg, 1, END_MODE_RESTART);
    hal_i2cRead(_slaveAddress, outData, nData, END_MODE_STOP);
}
/* --------------------------------------------------------- User Functions - */

void temphum6_reset()
{
    uint8_t writeReg[ 2 ];
    
    writeReg[ 0 ] = _TEMPHUM6_REG_SYSTEM_CONTROL;
    writeReg[ 1 ] = 0x80;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeReg, 2, END_MODE_STOP);
    
    BOOTING_TIME();
}

uint16_t temphum6_getPartID()
{
    volatile uint16_t ID;
    uint8_t readReg[2];
    
    temphum6_writeByte(_TEMPHUM6_REG_SYSTEM_CONTROL, _TEMPHUM6_LOW_POWER_DISABLE);
    BOOTING_TIME();

    temphum6_readData(_TEMPHUM6_REG_PART_ID, readReg, 2);
    ID = (readReg[ 1 ] << 8) | readReg[ 0 ];

    return ID;
}

void temphum6_RUN()
{
    temphum6_writeByte(_TEMPHUM6_REG_SENS_RUN, 
                       _TEMPHUM6_HUM_RUN_SINGLE_SHOT_MODE | 
                       _TEMPHUM6_TEMP_RUN_SINGLE_SHOT_MODE );
    
    temphum6_writeByte(_TEMPHUM6_REG_SENS_START, 
                       _TEMPHUM6_HUM_START_MEASUREMENT | 
                       _TEMPHUM6_TEMP_START_MEASUREMENT );
}

void temphum6_STOP(uint8_t stop_cfg)
{
    temphum6_writeByte(_TEMPHUM6_REG_SENS_STOP,
                       _TEMPHUM6_HUM_STOP_CONTINUOUS_MEASUREMENT |
                       _TEMPHUM6_TEMP_STOP_CONTINUOUS_MEASUREMENT );
}

float temphum6_readTemperature(uint8_t tempIn)
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 3 ];
    volatile uint32_t Temperature;
    uint8_t status;
    uint16_t TEMP;
    
    temphum6_RUN();
    SINGLE_TIME();
    
    writeReg[ 0 ] = _TEMPHUM6_REG_TEMPERATURE;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeReg, 1, END_MODE_RESTART);
    hal_i2cRead(_slaveAddress, readReg, 3, END_MODE_STOP);
    
    Temperature = (readReg[ 2 ] << 16) + (readReg[ 1 ] << 8) + readReg[ 0 ];

    _extract(Temperature,&TEMP,&status);

    if(tempIn == _TEMPHUM6_TEMP_IN_FAHRENHEIT)
    {
        return ((((float)TEMP / 64) - 273.15)* 1.8 + 32.0);
    }
    else if(tempIn == _TEMPHUM6_TEMP_IN_KELVIN)
    {
        return (((float)TEMP / 64));
    }
    else
    {
        return (((float)TEMP / 64) - 273.15);
    }
}

float temphum6_readRelativeHuminidy()
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 3 ];
    volatile uint32_t Huminidy;
    uint8_t status;
    uint16_t HUM;

    temphum6_RUN();
    SINGLE_TIME();

    writeReg[ 0 ] = _TEMPHUM6_REG_RELATIVE_HUMIDITY;

    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, writeReg, 1, END_MODE_RESTART);
    hal_i2cRead(_slaveAddress, readReg, 3, END_MODE_STOP);

    Huminidy = (readReg[ 2 ] << 16) + (readReg[1] << 8) + readReg[0];

    _extract(Huminidy,&HUM,&status);

    return ((float)HUM / 512.0);
}

/* -------------------------------------------------------------------------- */
/*
  __temphum6_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */