/*  Derya Y. iiot2k@gmail.com
*   MIT license
*   LCD driver
*/

#include <SPI.h>
#include <U8g2lib.h> // https://github.com/olikraus/u8g2

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, 10, 9, 8, U8X8_PIN_NONE);  

char line1_store[10]; 
char line2_store[50]; 

// configure LCD
void display_setup()
{
  strncpy(line1_store, "--:--", sizeof(line1_store)); 
  strncpy(line2_store, "--.-°C --.-%", sizeof(line2_store)); 

  u8g2.begin();
  u8g2.clear();
}

// Refresh LCD from line store
void display_update()
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_fub35_tn);
  u8g2.drawUTF8(0, 36, line1_store);

  u8g2.drawLine(0, 40, 127, 40);
  u8g2.drawLine(0, 41, 127, 41);
  u8g2.setFont(u8g2_font_helvR14_te);
  u8g2.drawUTF8(2, 60, line2_store);

  u8g2.updateDisplay();
}

// display message on LCD
void display_message(String line)
{
  u8g2.clearBuffer();
  u8g2.drawLine(0, 38, 127, 38);
  u8g2.setFont(u8g2_font_t0_13_te);
  u8g2.drawUTF8(2, 55, line.substring(0,18).c_str());
  u8g2.updateDisplay();
}

// display clock on line 1
void display_setclock()
{
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  strftime(line1_store, sizeof(line1_store), "%H:%M", &timeinfo);
  display_update();
}

// write to line 2
void display_update_line2(String line)
{
  strncpy(line2_store, line.substring(0,18).c_str(), sizeof(line2_store)); 
  display_update();
}
