#include "WS2812B.h"
//***************************************************************************
// WS2812B.c  LED Strip Display Demo Program
// For PIC 18F13K22
// Crystal 16 MHz  HSPLL 64Mhz
// Works with WS2812B/WS2812 LED
// LED Sequence Speed Pot RC5 = ADC_Read(5)
// LED Order is G, R, B.   verify Colors in WS2812B.h
// 4 LED Strip with  - +5V, IN, GND
//***************************************************************************
//Variable Declarations
//***************************************************************************
unsigned char step, counter, temp1;
//****************************************************************************
void main(void) 
{
  ANSELH = 0b00010000;        // RA5 is Analog In
  PORTC=0;
  TRISC.RC1=1;  //Input to receive data from LDR
  TRISC.RC7=0; //SDO is output for sending commands thru SPI
//****************************************************************************
// Initialize Serial LCD Display
//****************************************************************************
  ADC_Init();  
  temp1 = ADC_Read(5); // Channel ANS5 is selected to read and convert the data from LDR
  Delay_ms(400);
// Set up MCU for proper bit rate for WS2812B LED
  SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV16, _SPI_DATA_SAMPLE_MIDDLE,_SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);
  delay_ms(250);
  WS2812_LEDCount(4);              // Sets Total Number of LEDS in strip
  Solid_Strip(black);               // Clears Strip
//****************************************************************************
while(1 == 1)
{  
   if(temp1 >= 150)        // If digital value is greater than 150.
   {
   InsertColor(red);
   delay_ms(200);
   }
   if(temp1 <= 151)
   {
   InsertColor(white);
   delay_ms(200);
   }
   InsertColor(blue);
  }// End While
}// End Main
//****************************************************************************
