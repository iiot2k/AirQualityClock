/*  Derya Y. iiot2k@gmail.com
*   MIT license
*   Control of LCD background light with LDR
*/

#define LIGHT_SENSOR_PIN A1
#define LCD_LED_PIN 2

#define INTENSITY_DARK    5
#define INTENSITY_DIM     10
#define INTENSITY_LIGTH   50
#define INTENSITY_BRIGTH  100
#define INTENSITY_HBRIGTH 255

int actual_intensity = INTENSITY_LIGTH;
int target_intensity = INTENSITY_LIGTH;

// configure LDR analog input and LCD light output 
void ldr_setup() 
{
  analogSetAttenuation(ADC_11db);
  pinMode(LCD_LED_PIN, OUTPUT);
  analogWrite(LCD_LED_PIN, INTENSITY_LIGTH);
}

// set LCD background light intensity
void ldr_set()
{
  if (target_intensity == actual_intensity)
    return;
  else if (target_intensity < actual_intensity)
    actual_intensity--;
  else if (target_intensity > actual_intensity)
    actual_intensity++;

  analogWrite(LCD_LED_PIN, actual_intensity);
}

// check LDR value
void ldr_check()
{
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  
  target_intensity = INTENSITY_HBRIGTH;

  if (analogValue < 40)
    target_intensity = INTENSITY_DARK;
  else if (analogValue < 800) 
    target_intensity = INTENSITY_DIM;
  else if (analogValue < 2000) 
    target_intensity = INTENSITY_LIGTH;
  else if (analogValue < 3200) 
    target_intensity = INTENSITY_BRIGTH;
}
