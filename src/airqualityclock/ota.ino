/*  Derya Y. iiot2k@gmail.com
*   MIT license
*   OTA handling
*/

#include <ArduinoOTA.h>

void ota_onstart();
void ota_onerror(ota_error_t ota_error); 

// configure and start OTA
void ota_setup() 
{
  ArduinoOTA.setHostname("airqualityclock");
  ArduinoOTA.onStart(ota_onstart);
  ArduinoOTA.onError(ota_onerror);
  ArduinoOTA.begin();
}

// check if OTO starts
void ota_handle()
{
  ArduinoOTA.handle();
}

// called on start of OTA
void ota_onstart() 
{
  display_message("Update clock " SW_VERSION);
}

// called on error of OTA
void ota_onerror(ota_error_t ota_error) 
{
  switch(ota_error)
  {
    case OTA_AUTH_ERROR: display_message("Auth Failed"); break;
    case OTA_BEGIN_ERROR: display_message("Begin Failed"); break;
    case OTA_CONNECT_ERROR: display_message("Connect Failed"); break;
    case OTA_RECEIVE_ERROR: display_message("Receive Failed"); break;
    case OTA_END_ERROR: display_message("End Failed"); break;
    default: display_message("Unknown");
  }
}



