/*
Example for TempHum6 Click

    Date          : nov 2018.
    Author        : Katarina Perendic

Test configuration TIVA :
    
    MCU              : TM4C129XNCZAD
    Dev. Board       : EasyMx PRO v7 for TIVA ARM
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module
- Application Initialization - Initialization driver init and reset device and read Part ID
- Application Task - (code snippet) - Reads Temperature and Huminidy data and logs this data to USBUART every 1sec.

*/

#include "Click_TempHum6_types.h"
#include "Click_TempHum6_config.h"

void systemInit()
{
    mikrobus_i2cInit( _MIKROBUS1, &_TEMPHUM6_I2C_CFG[0] );
    mikrobus_logInit( _LOG_USBUART_A, 9600 );
    mikrobus_logWrite("--- System Init ---", _LOG_LINE);
    Delay_ms( 100 );
}

void applicationInit()
{
    uint16_t PartID;
    
    temphum6_i2cDriverInit( (T_TEMPHUM6_P)&_MIKROBUS1_GPIO, (T_TEMPHUM6_P)&_MIKROBUS1_I2C, _TEMPHUM6_DEVICE_SLAVE_ADDRESS );
    temphum6_reset();
    
    PartID = temphum6_getPartID();
    if(PartID == _TEMPHUM6_PART_ID)
    {
        mikrobus_logWrite("Device OK - read ID is OK", _LOG_LINE);
    }
    else
    {
        mikrobus_logWrite("Device ERROR - read ID is NOT OK", _LOG_LINE);
    }
}

void applicationTask()
{
    char demoText[50];
    float TEMP;
    float HUM;

    TEMP = temphum6_readTemperature(_TEMPHUM6_TEMP_IN_CELSIUS);
    FloatToStr(TEMP,demoText);
    mikrobus_logWrite("Temperature is  ", _LOG_TEXT);
    mikrobus_logWrite(demoText, _LOG_TEXT);
    mikrobus_logWrite(" C", _LOG_LINE);
    
    HUM = temphum6_readRelativeHuminidy();
    FloatToStr(HUM,demoText);
    mikrobus_logWrite("Huminidy is ", _LOG_TEXT);
    mikrobus_logWrite(demoText, _LOG_TEXT);
    mikrobus_logWrite(" %RH", _LOG_LINE);
    
    mikrobus_logWrite("------------------", _LOG_LINE);
    Delay_ms( 1000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}