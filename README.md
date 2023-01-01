# Switchboard 

A very simple switchboard for little kids made from scrap parts for xmas. Contains a DFPlayer mini with a speaker, a vibration motor, and a Neopixel LED as outputs. Each is connected to a banana connector wire that can be plugged in into a 3x3 switchboard. Depending on where it's plugged, different stuff happens. Furthermore, consists of 2 switches and 2 USB-A sockets for adding usb-powered peripherals and an internal power bank. Uses ATmega324p at its heart. 

## Sounds

Sounds from https://www.zapsplat.com/. Each option selects a specific sound and plays it once. 

## Motor

Different holes vibrate the motor with different strength and different duration. 

## Lights

- red, green, blue, white (4)
- red, green, blue, white breathing (4)
- red, green, blue, white 
- yellow construction siren light
- red alternating
- blue alternating
- blue - red alternating
 





# TODO 



## ATMega324pa

- [https://www.engbedded.com/fusecalc/] for fuses calculator
- needs external oscillator to work properly
- uses avrdude & usbtiny to program
- make sure the -D is not passed to avrdude by specifying own upload command

## DFPlayer

- [https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299] 
- [https://circuitjournal.com/how-to-use-the-dfplayer-mini-mp3-module-with-an-arduino#preparing-sd-card]
- won't register as working unless there is some mp3 to play

## Devel Server

- picocom -b 115200 /dev/ttyAMA0
- C-a C-q to exit
- udev rules for avrdude non-root access