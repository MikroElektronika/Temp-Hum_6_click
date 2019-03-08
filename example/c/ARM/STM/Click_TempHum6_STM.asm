_systemInit:
;Click_TempHum6_STM.c,30 :: 		void systemInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_TempHum6_STM.c,32 :: 		mikrobus_i2cInit( _MIKROBUS1, &_TEMPHUM6_I2C_CFG[0] );
MOVW	R0, #lo_addr(__TEMPHUM6_I2C_CFG+0)
MOVT	R0, #hi_addr(__TEMPHUM6_I2C_CFG+0)
MOV	R1, R0
MOVS	R0, #0
BL	_mikrobus_i2cInit+0
;Click_TempHum6_STM.c,33 :: 		mikrobus_logInit( _LOG_USBUART_A, 9600 );
MOVW	R1, #9600
MOVS	R0, #32
BL	_mikrobus_logInit+0
;Click_TempHum6_STM.c,34 :: 		mikrobus_logWrite("--- System Init ---", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr1_Click_TempHum6_STM+0)
MOVT	R0, #hi_addr(?lstr1_Click_TempHum6_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,35 :: 		Delay_ms( 100 );
MOVW	R7, #20351
MOVT	R7, #18
NOP
NOP
L_systemInit0:
SUBS	R7, R7, #1
BNE	L_systemInit0
NOP
NOP
NOP
;Click_TempHum6_STM.c,36 :: 		}
L_end_systemInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _systemInit
_applicationInit:
;Click_TempHum6_STM.c,38 :: 		void applicationInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_TempHum6_STM.c,42 :: 		temphum6_i2cDriverInit( (T_TEMPHUM6_P)&_MIKROBUS1_GPIO, (T_TEMPHUM6_P)&_MIKROBUS1_I2C, _TEMPHUM6_DEVICE_SLAVE_ADDRESS );
MOVS	R2, __TEMPHUM6_DEVICE_SLAVE_ADDRESS
MOVW	R1, #lo_addr(__MIKROBUS1_I2C+0)
MOVT	R1, #hi_addr(__MIKROBUS1_I2C+0)
MOVW	R0, #lo_addr(__MIKROBUS1_GPIO+0)
MOVT	R0, #hi_addr(__MIKROBUS1_GPIO+0)
BL	_temphum6_i2cDriverInit+0
;Click_TempHum6_STM.c,43 :: 		temphum6_reset();
BL	_temphum6_reset+0
;Click_TempHum6_STM.c,45 :: 		PartID = temphum6_getPartID();
BL	_temphum6_getPartID+0
;Click_TempHum6_STM.c,46 :: 		if(PartID == _TEMPHUM6_PART_ID)
MOVW	R1, __TEMPHUM6_PART_ID
MOVT	R1, __TEMPHUM6_PART_ID+2
CMP	R0, R1
IT	NE
BNE	L_applicationInit2
;Click_TempHum6_STM.c,48 :: 		mikrobus_logWrite("Device OK - read ID is OK", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr2_Click_TempHum6_STM+0)
MOVT	R0, #hi_addr(?lstr2_Click_TempHum6_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,49 :: 		}
IT	AL
BAL	L_applicationInit3
L_applicationInit2:
;Click_TempHum6_STM.c,52 :: 		mikrobus_logWrite("Device ERROR - read ID is NOT OK", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr3_Click_TempHum6_STM+0)
MOVT	R0, #hi_addr(?lstr3_Click_TempHum6_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,53 :: 		}
L_applicationInit3:
;Click_TempHum6_STM.c,54 :: 		}
L_end_applicationInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _applicationInit
_applicationTask:
;Click_TempHum6_STM.c,56 :: 		void applicationTask()
SUB	SP, SP, #56
STR	LR, [SP, #0]
;Click_TempHum6_STM.c,62 :: 		TEMP = temphum6_readTemperature(_TEMPHUM6_TEMP_IN_CELSIUS);
MOVS	R0, __TEMPHUM6_TEMP_IN_CELSIUS
BL	_temphum6_readTemperature+0
;Click_TempHum6_STM.c,63 :: 		FloatToStr(TEMP,demoText);
ADD	R1, SP, #4
BL	_FloatToStr+0
;Click_TempHum6_STM.c,64 :: 		mikrobus_logWrite("Temperature is  ", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr4_Click_TempHum6_STM+0)
MOVT	R0, #hi_addr(?lstr4_Click_TempHum6_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,65 :: 		mikrobus_logWrite(demoText, _LOG_TEXT);
ADD	R0, SP, #4
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,66 :: 		mikrobus_logWrite(" C", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr5_Click_TempHum6_STM+0)
MOVT	R0, #hi_addr(?lstr5_Click_TempHum6_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,68 :: 		HUM = temphum6_readRelativeHuminidy();
BL	_temphum6_readRelativeHuminidy+0
;Click_TempHum6_STM.c,69 :: 		FloatToStr(HUM,demoText);
ADD	R1, SP, #4
BL	_FloatToStr+0
;Click_TempHum6_STM.c,70 :: 		mikrobus_logWrite("Huminidy is ", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr6_Click_TempHum6_STM+0)
MOVT	R0, #hi_addr(?lstr6_Click_TempHum6_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,71 :: 		mikrobus_logWrite(demoText, _LOG_TEXT);
ADD	R0, SP, #4
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,72 :: 		mikrobus_logWrite(" %RH", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr7_Click_TempHum6_STM+0)
MOVT	R0, #hi_addr(?lstr7_Click_TempHum6_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,74 :: 		mikrobus_logWrite("------------------", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr8_Click_TempHum6_STM+0)
MOVT	R0, #hi_addr(?lstr8_Click_TempHum6_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_TempHum6_STM.c,75 :: 		Delay_ms( 1000 );
MOVW	R7, #6911
MOVT	R7, #183
NOP
NOP
L_applicationTask4:
SUBS	R7, R7, #1
BNE	L_applicationTask4
NOP
NOP
NOP
;Click_TempHum6_STM.c,76 :: 		}
L_end_applicationTask:
LDR	LR, [SP, #0]
ADD	SP, SP, #56
BX	LR
; end of _applicationTask
_main:
;Click_TempHum6_STM.c,78 :: 		void main()
SUB	SP, SP, #4
;Click_TempHum6_STM.c,80 :: 		systemInit();
BL	_systemInit+0
;Click_TempHum6_STM.c,81 :: 		applicationInit();
BL	_applicationInit+0
;Click_TempHum6_STM.c,83 :: 		while (1)
L_main6:
;Click_TempHum6_STM.c,85 :: 		applicationTask();
BL	_applicationTask+0
;Click_TempHum6_STM.c,86 :: 		}
IT	AL
BAL	L_main6
;Click_TempHum6_STM.c,87 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
