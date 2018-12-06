@echo off
set COM_PORT=%1
set HEX_FILE=%2

set AVRDUDE_BIN="C:\Users\Brian\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino14/bin/avrdude"
set AVRDUDE_CONF="C:\Users\Brian\AppData\Local\Arduino15\packages\MicroCore\hardware\avr\1.0.3/avrdude.conf"

ECHO Port is set to - %COM_PORT%
ECHO Hex File is set to -  %HEX_FILE%

setlocal
:PROMPT
SET /P AREYOUSURE=Burn Next Chip (Y/[N])?
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END

ECHO --------------------
ECHO Burning Bootloader 
ECHO --------------------

ECHO Doing the first thing
CALL %AVRDUDE_BIN% -C%AVRDUDE_CONF% -v -pattiny13 -carduino -B32 -P%COM_PORT% -b19200 -e -Ulock:w:0x3f:m -Uhfuse:w:0xff:m -Ulfuse:w:0x3A:m
ECHO Doing the second thing
CALL %AVRDUDE_BIN% -C%AVRDUDE_CONF% -v -pattiny13 -carduino -B32 -P%COM_PORT% -b19200 -Ulock:w:0x3e:m 

ECHO --------------------
ECHO Burning Sketch 
ECHO --------------------
CALL %AVRDUDE_BIN% -C%AVRDUDE_CONF% -v -pattiny13 -carduino -P%COM_PORT% -b19200 -Uflash:w:%HEX_FILE%:i

goto PROMPT

:END
endlocal