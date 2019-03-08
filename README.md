![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# TempHum6 Click

- **CIC Prefix**  : TEMPHUM6
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : nov 2018.

---

### Software Support

We provide a library for the TempHum6 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2646/temp-hum-6-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library initializes and defines the I2C bus driver and drivers that offer a choice for writing data in register and reads data form register.
The library includes function for read Temperature and Relative Huminidy data and function for read device part ID data.
The user also has the function for RUN and STOP procedure and function for reset device.

Key functions :

- ``` float temphum6_readTemperature(uint8_t tempIn) ``` - Functions for read Temperature data
- ``` float temphum6_readRelativeHuminidy() ``` - Functions for read Relative Huminidy data
- ``` void temphum6_reset() ``` - Functions for reset device

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module
- Application Initialization - Initialization driver init and reset device and read Part ID
- Application Task - (code snippet) - Reads Temperature and Huminidy data and logs this data to USBUART every 1sec.

```.c
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
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2646/temp-hum-6-click) page.

Other mikroE Libraries used in the example:

- I2C

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
