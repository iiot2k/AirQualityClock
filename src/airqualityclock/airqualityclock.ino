/*  Derya Y. iiot2k@gmail.com
*   MIT license
*   Clock main program
*/

#define SW_VERSION "1.0"

uint32_t ldr_tick = 0;
#define LDR_TICK 4000 // 4s

uint32_t ldr_tick_set = 0;
#define LDR_TICK_SET 100 // 100ms

uint32_t clock_tick = 0;
#define CLOCK_TICK 1000 // 1s

uint32_t watchdog_tick = 0;
#define WATCHDOG_TICK 300000 // 300s

bool sensor_ok = false;

// called on program start
void setup()
{
  // setup display lcd
  display_setup();

  // setup LDR
  ldr_setup();

  // setup sensor
  sensor_ok = sensor_setup();

  // connect to wlan
  wlan_setup();

  // setup ota
  if (wlan_isconnected())
    ota_setup();
  
  uint32_t t_now = millis();

  // init ticks
  ldr_tick = t_now;
  ldr_tick_set = t_now;
  clock_tick = t_now;
  watchdog_tick = t_now;
}

// called in endless loop
void loop() 
{
  uint32_t t_now = millis();

  // if wlan connected update clock and check for OTA
  if (wlan_isconnected())
  {
    ota_handle();

    if ((t_now - clock_tick) > CLOCK_TICK)
    {
      display_setclock();
      clock_tick = t_now;
    }
  }
  // if not connected, restart after 300s
  else if ((t_now - watchdog_tick) > WATCHDOG_TICK)
    ESP.restart();

  // check LDR
  if ((t_now - ldr_tick) > LDR_TICK)
  {
    ldr_check();
    ldr_tick = t_now;
  }

  // set display intens.
  if ((t_now - ldr_tick_set) > LDR_TICK_SET)
  {
    ldr_set();
    ldr_tick_set = t_now;
  }
  
  // check sensor
  if (sensor_ok)
    sensor_check();
}
