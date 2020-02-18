# WS2812B-with-PIC18F13K22
PIC18F13K22 with WS2812B SPI bit banging
  
This program is written to configure LEDs WS2812B via PIC microcontroller using PIC18F13K22.
This program is written in mickroc for PIC software. It contains two files one header and second C file.
Header file contains bit banging which transfers data thru SPI. Different functions are written to set the colors of 4 LEDs. 
And that functions is called in main file.Main file takes input from Light dependant resistor and depending on ADC conversion
it sends the data to SDO pin of SPI module.
