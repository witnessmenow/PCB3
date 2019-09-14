#!/bin/bash

# Install AVRDude from Brew
# http://macappstore.org/avrdude/

COM_PORT=$1
HEX_FILE=$2

AVRDUDE_BIN="/usr/local/bin/avrdude"
AVRDUDE_CONF="/Users/brian/Library/Arduino15/packages/MicroCore/hardware/avr/1.0.4/avrdude.conf"

echo "Port is set to - $COM_PORT"
echo "Hex File is set to -  $HEX_FILE"

echo "Burn Next Chip (Y/[N])?"
read areYouSure

while [ $areYouSure = "Y" ] || [ $areYouSure = "y"  ]
do
    echo --------------------
    echo Burning Bootloader 
    echo --------------------

    echo Doing the first thing
    $AVRDUDE_BIN -C$AVRDUDE_CONF -v -pattiny13 -carduino -B32 -P$COM_PORT -b19200 -e -Ulock:w:0x3f:m -Uhfuse:w:0xff:m -Ulfuse:w:0x3A:m
    echo Doing the second thing
    $AVRDUDE_BIN -C$AVRDUDE_CONF -v -pattiny13 -carduino -B32 -P$COM_PORT -b19200 -Ulock:w:0x3e:m 

    echo --------------------
    echo Burning the sketch 
    echo --------------------

    $AVRDUDE_BIN -C$AVRDUDE_CONF -v -pattiny13 -carduino -P$COM_PORT -b19200 -Uflash:w:$HEX_FILE:i

    echo "Burn Next Chip (Y/[N])?"
    read areYouSure
done

echo --------------------
echo Good Bye! 
echo --------------------