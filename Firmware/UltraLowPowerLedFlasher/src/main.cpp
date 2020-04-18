#include <Arduino.h>
#include "TWI_master.h"

const byte VEML7700_ADDRESS = 0x20;
TwiWire wire;
byte dataIn[2];
byte dataOut[1] = {0x00};

void setup()
{
  wire.begin();
  wire.beginTransmission(VEML7700_ADDRESS);
  if (wire.writeEndTransmission(dataOut, 1, false))
  {
    wire.readRequestFrom(VEML7700_ADDRESS, dataIn, 2);
  }
}

void loop()
{
}