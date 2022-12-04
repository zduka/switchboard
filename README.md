# Switchboard 

A very simple switchboard for little kids made from scrap parts for xmas. Contains a DFPlayer mini with a speaker, a vibration motor, and a Neopixel LED as outputs. Each is connected to a banana connector wire that can be plugged in into a 3x3 switchboard. Depending on where it's plugged, different stuff happens. Furthermore, consists of 2 switches and 2 USB-A sockets for adding usb-powered peripherals and an internal power bank. Uses ATmega324p at its heart. 

# TODO 

- get & test a power bank


## ATMega324pa

- [https://www.engbedded.com/fusecalc/] for fuses calculator
- needs external oscillator to work properly
- uses avrdude & usbtiny to program
- make sure the -D is not passed to avrdude by specifying own upload command

## DFPlayer

- [https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299] 
- won't register as working unless there is some mp3 to play

## Devel Server

- picocom -b 115200 /dev/ttyAMA0
- C-a C-q to exit
