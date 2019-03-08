#line 1 "D:/Clicks_git/T/Temp-Hum_6_click/SW/example/c/ARM/STM/Click_TempHum6_STM.c"
#line 1 "d:/clicks_git/t/temp-hum_6_click/sw/example/c/arm/stm/click_temphum6_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 1 "d:/clicks_git/t/temp-hum_6_click/sw/example/c/arm/stm/click_temphum6_config.h"
#line 1 "d:/clicks_git/t/temp-hum_6_click/sw/example/c/arm/stm/click_temphum6_types.h"
#line 19 "d:/clicks_git/t/temp-hum_6_click/sw/example/c/arm/stm/click_temphum6_config.h"
const uint32_t _TEMPHUM6_I2C_CFG[ 1 ] =
{
 100000
};
#line 28 "D:/Clicks_git/T/Temp-Hum_6_click/SW/example/c/ARM/STM/Click_TempHum6_STM.c"
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

 temphum6_i2cDriverInit( ( const uint8_t* )&_MIKROBUS1_GPIO, ( const uint8_t* )&_MIKROBUS1_I2C, _TEMPHUM6_DEVICE_SLAVE_ADDRESS );
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
