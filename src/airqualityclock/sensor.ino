/*  Derya Y. iiot2k@gmail.com
*   MIT license
*   Sensor handling
*/

#include <bsec2.h> // bsec2 by Bosch Sensotec

Bsec2 envSensor;

void sensor_callback(const bme68xData data, const bsecOutputs outputs, Bsec2 bsec);

// configure i2c and sensor
bool sensor_setup() 
{
  bsecSensor sensorlist[] =
  {
    //BSEC_OUTPUT_IAQ,
    //BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_PRESSURE,
    //BSEC_OUTPUT_RAW_HUMIDITY,
    //BSEC_OUTPUT_RAW_GAS,
    //BSEC_OUTPUT_STABILIZATION_STATUS,
    //BSEC_OUTPUT_RUN_IN_STATUS,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
    //BSEC_OUTPUT_GAS_PERCENTAGE,
    //BSEC_OUTPUT_COMPENSATED_GAS
  };

  Wire.begin(SDA, SCL);

  if (!envSensor.begin(BME68X_I2C_ADDR_HIGH, Wire))
  {
    display_update_line2("E680");
    return false;
  }

	envSensor.setTemperatureOffset(TEMP_OFFSET_LP);
  envSensor.updateSubscription(sensorlist, ARRAY_LEN(sensorlist), BSEC_SAMPLE_RATE_LP);
  envSensor.attachCallback(sensor_callback);

  return true;
}

// check if data avaible on sensor
void sensor_check() 
{
  envSensor.run();
}

// convert IAQ value to level text depends on range
String iaq_to_text(uint32_t iaq)
{
  if (iaq <= 50)
    return "[0]";
  else if (iaq <= 100)
    return "[1]";
  else if (iaq <= 150)
    return "[2]";
  else if (iaq <= 200)
    return "[3]";
  else if (iaq <= 250)
    return "[4]";
  else if (iaq <= 350)
    return "[5]";
  else
    return "[6]";
}

#define MAX_LINE_SEQ 8

uint8_t line_seq = 0;

// called after data is avaiable on sensor
void sensor_callback(const bme68xData data, const bsecOutputs outputs, Bsec2 bsec)
{
  String output_line = "";
  char buffer[50];

  if (!outputs.nOutputs)
      return;

  for (uint8_t i = 0; i < outputs.nOutputs; i++)
  {
    const bsecData output  = outputs.output[i];

    switch (output.sensor_id)
    {
      case BSEC_OUTPUT_IAQ:
        break;
      case BSEC_OUTPUT_RAW_TEMPERATURE:
        break;
      case BSEC_OUTPUT_RAW_PRESSURE:
        if (line_seq == 1)
        {
          snprintf(buffer, sizeof(buffer), "%.0f mbar", output.signal);
          output_line += buffer;
        }
        break;
      case BSEC_OUTPUT_RAW_HUMIDITY:
        break;
      case BSEC_OUTPUT_RAW_GAS:
          break;
      case BSEC_OUTPUT_STABILIZATION_STATUS:
          break;
      case BSEC_OUTPUT_RUN_IN_STATUS:
          break;
      case BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE: 
        if ((line_seq == 0) || (line_seq == 2) || (line_seq == 4) || (line_seq == 6))
        {
          snprintf(buffer, sizeof(buffer), "%.1f°C ", output.signal);
          output_line = buffer;
        }
        break;
      case BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY: 
        if ((line_seq == 0) || (line_seq == 2) || (line_seq == 4) || (line_seq == 6))
        {
          snprintf(buffer, sizeof(buffer), "%.0f%%", output.signal);
          output_line += buffer;
        }
        break;
      case BSEC_OUTPUT_STATIC_IAQ:
        if (line_seq == 3)
        {
          snprintf(buffer, sizeof(buffer), "%.0f ", output.signal);
          output_line = "IAQ: ";
          output_line += buffer;
          output_line += iaq_to_text(output.signal);
        }
        break;
      case BSEC_OUTPUT_CO2_EQUIVALENT:
        if (line_seq == 5)
        {
          snprintf(buffer, sizeof(buffer), "%.0fppm", output.signal);
          output_line = "CO2: ";
          output_line += buffer;
        }
        break;
      case BSEC_OUTPUT_BREATH_VOC_EQUIVALENT:
        if (line_seq == 7)
        {
          snprintf(buffer, sizeof(buffer), "%.0fppm", output.signal);
          output_line = "VOC: ";
          output_line += buffer;
        }
        break;
      case BSEC_OUTPUT_GAS_PERCENTAGE:
          break;
      case BSEC_OUTPUT_COMPENSATED_GAS:
          break;
      default:
          break;
    }
  }
  
  line_seq++;
  
  if (line_seq == MAX_LINE_SEQ)
    line_seq = 0;

  display_update_line2(output_line);
}
