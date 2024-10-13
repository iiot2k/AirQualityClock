/*  Derya Y. iiot2k@gmail.com
*   MIT license
*   WLAN handling
*/

#include <WiFi.h> 

// change for your wifi
#define WIFI_SSID "****"
#define WIFI_PASSW "****"

// check if wlan connected
bool wlan_isconnected()
{
  return (WiFi.status() == WL_CONNECTED);
}

// configure wlan and connect
void wlan_setup() 
{
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSW);

    // connect to wlan
    for (uint8_t cnt = 0; cnt < 20; cnt++)
    {
      if (WiFi.status() == WL_CONNECTED)
      {
        // set timezone and ntp server
        configTzTime("CET-1CEST,M3.5.0/03,M10.5.0/03", "de.pool.ntp.org");
        return;
      }

      delay(500);
    }

    display_message("No WiFi");
}
