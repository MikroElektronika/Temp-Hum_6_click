/*
    __temphum6_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __temphum6_driver.h
@brief    TempHum6 Driver
@mainpage TempHum6 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   TEMPHUM6
@brief      TempHum6 Click Driver
@{

| Global Library Prefix | **TEMPHUM6** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **nov 2018.**      |
| Developer             | **Katarina Perendic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _TEMPHUM6_H_
#define _TEMPHUM6_H_

/** 
 * @macro T_TEMPHUM6_P
 * @brief Driver Abstract type 
 */
#define T_TEMPHUM6_P    const uint8_t*

/** @defgroup TEMPHUM6_COMPILE Compilation Config */              /** @{ */

//  #define   __TEMPHUM6_DRV_SPI__                            /**<     @macro __TEMPHUM6_DRV_SPI__  @brief SPI driver selector */
   #define   __TEMPHUM6_DRV_I2C__                            /**<     @macro __TEMPHUM6_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __TEMPHUM6_DRV_UART__                           /**<     @macro __TEMPHUM6_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup TEMPHUM6_VAR Variables */                           /** @{ */

/* Chip constants */
extern const uint16_t _TEMPHUM6_PART_ID;
extern const uint8_t _TEMPHUM6_DEVICE_SLAVE_ADDRESS;

/* Status */
extern const uint8_t _TEMPHUM6_STATUS_I2CERROR;
extern const uint8_t _TEMPHUM6_STATUS_CRCERROR;
extern const uint8_t _TEMPHUM6_STATUS_INVALID;
extern const uint8_t _TEMPHUM6_STATUS_OK;

/* Temperature data in ...*/
extern const uint8_t _TEMPHUM6_TEMP_IN_FAHRENHEIT ;
extern const uint8_t _TEMPHUM6_TEMP_IN_KELVIN     ;
extern const uint8_t _TEMPHUM6_TEMP_IN_CELSIUS    ;

/* Register */
extern const uint8_t _TEMPHUM6_REG_PART_ID              ;
extern const uint8_t _TEMPHUM6_REG_UNIQUE_IDENTIFIER    ;
extern const uint8_t _TEMPHUM6_REG_SYSTEM_CONTROL       ;
extern const uint8_t _TEMPHUM6_REG_SYSTEM_STATUS        ;
extern const uint8_t _TEMPHUM6_REG_SENS_RUN             ;
extern const uint8_t _TEMPHUM6_REG_SENS_START           ;
extern const uint8_t _TEMPHUM6_REG_SENS_STOP            ;
extern const uint8_t _TEMPHUM6_REG_SENS_STATUS          ;
extern const uint8_t _TEMPHUM6_REG_TEMPERATURE          ;
extern const uint8_t _TEMPHUM6_REG_RELATIVE_HUMIDITY    ;

/* Controls the system */
extern const uint8_t _TEMPHUM6_LOW_POWER_DISABLE ;
extern const uint8_t _TEMPHUM6_LOW_POWER_ENABLE  ;

/* System status */
extern const uint8_t _TEMPHUM6_SYSTEM_IS_IN_STANDBY_OR_BOOTING_STATE ;
extern const uint8_t _TEMPHUM6_SYSTEM_IS_IN_ACTIVE_STATE             ;

/* Register configures the run modes */
extern const uint8_t _TEMPHUM6_HUM_RUN_SINGLE_SHOT_MODE  ;
extern const uint8_t _TEMPHUM6_TEMP_RUN_SINGLE_SHOT_MODE ;
extern const uint8_t _TEMPHUM6_HUM_RUN_CONTINUOUS_MODE   ;
extern const uint8_t _TEMPHUM6_TEMP_RUN_CONTINUOUS_MODE  ;

/* Starts a measurement for the sensors */
extern const uint8_t _TEMPHUM6_HUM_START_MEASUREMENT  ;
extern const uint8_t _TEMPHUM6_TEMP_START_MEASUREMENT ;
extern const uint8_t _TEMPHUM6_DISABLE_MEASUREMENT    ;

/* Stops a continuous measurement */
extern const uint8_t _TEMPHUM6_HUM_STOP_CONTINUOUS_MEASUREMENT ;
extern const uint8_t _TEMPHUM6_TEMP_STOP_CONTINUOUS_MEASUREMENT;
extern const uint8_t _TEMPHUM6_DISABLE_CONTINUOUS_MEASUREMENT  ;


                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup TEMPHUM6_INIT Driver Initialization */              /** @{ */

#ifdef   __TEMPHUM6_DRV_SPI__
void temphum6_spiDriverInit(T_TEMPHUM6_P gpioObj, T_TEMPHUM6_P spiObj);
#endif
#ifdef   __TEMPHUM6_DRV_I2C__
void temphum6_i2cDriverInit(T_TEMPHUM6_P gpioObj, T_TEMPHUM6_P i2cObj, uint8_t slave);
#endif
#ifdef   __TEMPHUM6_DRV_UART__
void temphum6_uartDriverInit(T_TEMPHUM6_P gpioObj, T_TEMPHUM6_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void temphum6_gpioDriverInit(T_TEMPHUM6_P gpioObj);
                                                                       /** @} */
/** @defgroup TEMPHUM6_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Functions for write N byte in registers
 *
 * @param[in] reg     Start register address
 * @param[in] InData  Data buffer
 * @param[in] nData   Number of bytes
 */
void temphum6_writeData(uint8_t reg, uint8_t *InData, uint8_t nData);

/**
 * @brief Functions for write one byte in register
 *
 * @param[in] reg    Register in which the data will be written
 * @param[in] _data  Data which be written in the register
 */
void temphum6_writeByte(uint8_t reg, uint8_t _data);

/**
 * @brief Functions for read data from registers
 *
 * @param[in]  reg       Start register address
 * @param[out] outData   Output Data buffer
 * @param[in]  nData     Number of bytes
 */
void temphum6_readData(uint8_t reg, uint8_t *outData, uint8_t nData);

/**
 * @brief Functions for reset device
 */
void temphum6_reset();

/**
 * @brief Functions for get device PART ID
 *
 * @return 16bit device part id
 */
uint16_t temphum6_getPartID();

/**
 * @brief Functions for RUN measurement
 *
 * The function sets the registers _TEMPHUM6_REG_SENS_RUN and _TEMPHUM6_REG_SENS_START.
 * RUN   : ( _TEMPHUM6_HUM_RUN_SINGLE_SHOT_MODE | _TEMPHUM6_TEMP_RUN_SINGLE_SHOT_MODE )
 * START : ( _TEMPHUM6_HUM_START_MEASUREMENT | _TEMPHUM6_TEMP_START_MEASUREMENT )
 */
void temphum6_RUN();

/**
 * @brief Functions for STOP measurement
 *
 * The function sets the registers _TEMPHUM6_REG_SENS_STOP
 * STOP : ( _TEMPHUM6_HUM_STOP_CONTINUOUS_MEASUREMENT | _TEMPHUM6_TEMP_STOP_CONTINUOUS_MEASUREMENT )
 */
void temphum6_STOP(uint8_t stop_cfg);

/**
 * @brief Functions for read Temperature data
 *
 * @param[in] tempIn       Temperature in ... (FAHRENHEIT, KELVIN, CELSIUS)
 * @return Temperature data
 */
float temphum6_readTemperature(uint8_t tempIn);

/**
 * @brief Functions for read Relative Huminidy data
 *
 * @return Relative Huminidy data in [%RH]
 */
float temphum6_readRelativeHuminidy();


                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_TempHum6_STM.c
    @example Click_TempHum6_TIVA.c
    @example Click_TempHum6_CEC.c
    @example Click_TempHum6_KINETIS.c
    @example Click_TempHum6_MSP.c
    @example Click_TempHum6_PIC.c
    @example Click_TempHum6_PIC32.c
    @example Click_TempHum6_DSPIC.c
    @example Click_TempHum6_AVR.c
    @example Click_TempHum6_FT90x.c
    @example Click_TempHum6_STM.mbas
    @example Click_TempHum6_TIVA.mbas
    @example Click_TempHum6_CEC.mbas
    @example Click_TempHum6_KINETIS.mbas
    @example Click_TempHum6_MSP.mbas
    @example Click_TempHum6_PIC.mbas
    @example Click_TempHum6_PIC32.mbas
    @example Click_TempHum6_DSPIC.mbas
    @example Click_TempHum6_AVR.mbas
    @example Click_TempHum6_FT90x.mbas
    @example Click_TempHum6_STM.mpas
    @example Click_TempHum6_TIVA.mpas
    @example Click_TempHum6_CEC.mpas
    @example Click_TempHum6_KINETIS.mpas
    @example Click_TempHum6_MSP.mpas
    @example Click_TempHum6_PIC.mpas
    @example Click_TempHum6_PIC32.mpas
    @example Click_TempHum6_DSPIC.mpas
    @example Click_TempHum6_AVR.mpas
    @example Click_TempHum6_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __temphum6_driver.h

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