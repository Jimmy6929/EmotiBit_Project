/**************************************************************
 *  EmotiBit ONLY version
 *  (Display + Time functions removed completely)
 **************************************************************/

#include <Arduino.h>
#include "EmotiBit.h"

// ------------------------------
// Serial
// ------------------------------
#define SerialUSB SERIAL_PORT_USBVIRTUAL
const uint32_t SERIAL_BAUD = 2000000;

// ------------------------------
// EmotiBit
// ------------------------------
EmotiBit emotibit;
const size_t DATA_BUF_SIZE = EmotiBit::MAX_DATA_BUFFER_SIZE;
float dataBuf[DATA_BUF_SIZE];

// Latest sensor values
float lastPPG   = NAN;
float lastEDA   = NAN;
float lastTempC = NAN;

// ------------------------------
// EmotiBit button callbacks
// ------------------------------
void onShortButtonPress()
{
  if (emotibit.getPowerMode() == EmotiBit::PowerMode::NORMAL_POWER) {
    emotibit.setPowerMode(EmotiBit::PowerMode::WIRELESS_OFF);
    Serial.println("PowerMode::WIRELESS_OFF");
  } else {
    emotibit.setPowerMode(EmotiBit::PowerMode::NORMAL_POWER);
    Serial.println("PowerMode::NORMAL_POWER");
  }
}

void onLongButtonPress()
{
  emotibit.sleep();
}

// ------------------------------
// Read EmotiBit sensor data
// ------------------------------
void pollEmotiBitData()
{
  size_t n;

  // PPG
  n = emotibit.readData(EmotiBit::DataType::PPG_GREEN, dataBuf, DATA_BUF_SIZE);
  if (n > 0) lastPPG = dataBuf[n - 1];

  // EDA
  n = emotibit.readData(EmotiBit::DataType::EDA, dataBuf, DATA_BUF_SIZE);
  if (n > 0) lastEDA = dataBuf[n - 1];

  // Temperature
  n = emotibit.readData(EmotiBit::DataType::THERMOPILE, dataBuf, DATA_BUF_SIZE);
  if (n > 0) lastTempC = dataBuf[n - 1];
}

// ------------------------------
// Setup
// ------------------------------
void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(2000);

  // EmotiBit setup
  String inoFilename = __FILE__;
  inoFilename.replace("/", "\\");
  if (inoFilename.lastIndexOf("\\") != -1) {
    inoFilename = inoFilename.substring(
      inoFilename.lastIndexOf("\\") + 1,
      inoFilename.indexOf(".")
    );
  }

  emotibit.setup(inoFilename);
  emotibit.attachShortButtonPress(&onShortButtonPress);
  emotibit.attachLongButtonPress(&onLongButtonPress);
}

// ------------------------------
// Main loop
// ------------------------------
void loop()
{
  // Always let EmotiBit run its system tasks
  emotibit.update();

  // Collect sensor data
  pollEmotiBitData();

  // Debug print (optional)
  Serial.print("PPG: ");  Serial.print(lastPPG);
  Serial.print("  EDA: "); Serial.print(lastEDA);
  Serial.print("  TEMP: "); Serial.println(lastTempC);

  delay(1);
}



