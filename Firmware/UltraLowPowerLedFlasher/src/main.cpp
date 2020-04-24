#include <Arduino.h>
#include "TWI_master.h"

static bool writeRegister(byte reg, byte value);
static bool readRegister(byte reg, byte &value);
const byte RV3028_ADDR = 0xA4;
const byte REG_CTRL1 = 0x0F;
const byte EERD = 3;
TwiWire wire;


void setup()
{
  wire.begin();
  //automatic refresh function has to be disabled (EERD = 1): register 0Fh, bit 3
  if(!writeRegister(REG_CTRL1, 1<<EERD))
  {
    return;
  }
  //busy status bit EEbusy has to indicate, that the last transfer has been finished (EEbusy = 0)

  //Before entering the command 11h, 12h, 21h or 22h, EECMD has to be written with 00h.
  //Configuration EEPROM with RAM mirror, Address 2Bh and 30h to 37h: 35h EEPROM CLKOUT
  //3.15.4. EEPROM CLKOUT REGISTER
}

void loop()
{
}

bool writeRegister(byte reg, byte value)
{
  wire.beginTransmission(RV3028_ADDR);
  byte data[2] = {reg, value};
  return wire.writeEndTransmission(data, sizeof(data), true);
}

bool readRegister(byte reg, byte &value)
{
  wire.beginTransmission(RV3028_ADDR);
  byte data[1];
  if (!wire.writeEndTransmission(data, 1, false))
  {
    return false;
  }
  return wire.readRequestFrom(RV3028_ADDR, data, 1);
}