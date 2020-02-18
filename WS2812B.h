// Color Definitions     Order G, R, B
#define        red            0,255,0
#define        green          255,0,0
#define        blue           0,0,255
#define        black          0,0,0
#define        grey           40,40,40
#define        white          255,255,255

#define  testbit(var, bit)  ((var) & (1 <<(bit)))
#define  setbit(var, bit)   ((var) |= (1 << (bit)))
#define  clrbit(var, bit)   ((var) &= ~(1 << (bit)))
#define  ws2812_zero 0b10000000        // was 10000000
#define  ws2812_one  0b11110000        // was 11110000
#define  tail 10                       // Sets Tail Length for Comet Routine
//****************************************************************************
//Two commands are select to send the data 0 and 1 thru bit banging process in SPI.
//It transfers data according to the datasheet of WS2812B TH0 and TH1 timinings.
//****************************************************************************
//Variable Declarations
//****************************************************************************
char MAX_LED_COUNT;
signed long led_strip_colors[10]; // 10 colors out of 256 are selected because less memory
int i, j;
unsigned char last_event;
signed int v;
unsigned char brightness = 1;
unsigned int speede;
//****************************************************************************

//****************************************************************************
void WS2812_frame()      // This function transfers 24 bit data to WS2812b depending on the numbers of LEDs
{
  unsigned int i;
  unsigned long this_led;
  unsigned int loop;

  for(i = 0; i < MAX_LED_COUNT; i++)
  {
  this_led = led_strip_colors[i];
  for(loop = 0; loop < 24; loop++)
      {
      if(testbit(this_led, 23))
          {          // test fixed bit 23
          spi1_write(ws2812_one);
          }
      else
          {
          spi1_write(ws2812_zero);
          }
      this_led *= 2;  // march all the bits one position to the left so
      }
  }
  delay_us(75);
}
//****************************************************************************
//****************************************************************************
void WS2812_LEDCount(char vari)
{
  MAX_LED_COUNT = vari + 6;
  return;
}
//****************************************************************************
void Clear_Strip()
{
char pos;
    // Clear Strip
    for(pos = 0; pos < MAX_LED_COUNT; pos++)
       {
       led_strip_colors[pos] = 0x000000;
       }
       WS2812_frame();
}
//*********************************************************************************
// Convert separate R,G,B into packed 32-bit RGB color.
// Packed format is always RGB, regardless of LED strand color order.
unsigned long Strip_Color(char g, char r, char b)
   {
   return ((unsigned long)g << 16) | ((unsigned long)r <<  8) | b;
   }
//****************************************************************************
Set_Color(unsigned long rred, unsigned int ggreen, char bblue,char position)
{
   unsigned long temp, temp1;

   temp = 0;
   temp1 = 0;
   temp1 = (rred / brightness) << 16;
   temp = temp + temp1;
   temp1 = 0;
   temp1 = (ggreen / brightness) << 8;
   temp = temp + temp1;
   temp1 = 0;
   temp1 = (bblue / brightness);
   temp = temp + temp1;
   led_strip_colors[position] = temp;
}
//*****************************************************************************
//****************************************************************************
void Solid_Strip(char r1, char g1, char b1)
{
char pos;

    for(pos = 0; pos < MAX_LED_COUNT; pos++)
       {
       if(last_event == 1)
       {
       last_event = 0;
       return;
       }
       Set_Color(r1, g1, b1, pos);
       }
       WS2812_frame();
}
//****************************************************************************
void InsertColor(char r1, char g1, char b1)
{
  unsigned int x;
  unsigned long new_color = 0;

  for(x = (MAX_LED_COUNT - 1); x > 0; x--)
    {
    led_strip_colors[x] = led_strip_colors[x - 1];
    }
  Set_Color(r1, g1, b1, 0);
    if(last_event == 1)
    {
    last_event = 0;
    return;
    }
  WS2812_frame();
}
//*****************************************************************************
