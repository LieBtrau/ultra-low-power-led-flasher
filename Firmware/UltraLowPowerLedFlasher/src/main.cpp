#include <Arduino.h>
#include "TWI_master.h"

static bool writeRegister(byte reg, byte value);
static bool readRegister(byte reg, byte &value);
static bool eeprombusy(bool& busy);
const byte REF_STATUS = 0x0E;
const byte RV3028_ADDR = 0xA4;
const byte REG_CTRL1 = 0x0F;
const byte REG_EEADDR = 0x25;
const byte REG_EEDATA = 0x26;
const byte REG_EECMD = 0x27;
const byte REG_EECLKOUT = 0x35;
const byte EERD_bit = 3;
const byte EEBusy_bit = 7;
const byte CMD_WRITE_EEPROM = 0x21;
TwiWire wire;

void setup()
{
  wire.begin();
  //automatic refresh function has to be disabled (EERD = 1): register 0Fh, bit 3
  if (!writeRegister(REG_CTRL1, 1 << EERD_bit))
  {
    return;
  }
  bool busy=false;
  if(!eeprombusy(busy) || busy)
  {
    return;
  }
  //Configuration EEPROM with RAM mirror, Address 2Bh and 30h to 37h: 35h EEPROM CLKOUT
  //3.15.4. EEPROM CLKOUT REGISTER
  if (!writeRegister(REG_EEADDR, REG_EECLKOUT) ||
      !writeRegister(REG_EEDATA, 0xC3) ||
      //Before entering the command 11h, 12h, 21h or 22h, EECMD has to be written with 00h.
      !writeRegister(REG_EECMD, 0x00) ||
      !writeRegister(REG_EECMD, CMD_WRITE_EEPROM))
  {
    return;
  }
  //wait for eeprom
  while(eeprombusy(busy) && busy)
  {
    delay(10);
  }
  if (!writeRegister(REG_CTRL1, 0x00))
  {
    return;
  }
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
  if (!wire.writeEndTransmission(&reg, 1, false))
  {
    return false;
  }
  return wire.readRequestFrom(RV3028_ADDR, &value, 1);
}

bool eeprombusy(bool& busy)
{
    //busy status bit EEbusy has to indicate, that the last transfer has been finished (EEbusy = 0)
  byte status = 0;
  if (!readRegister(REF_STATUS, status))
  {
    return false;
  }
  busy = bitRead(status, EEBusy_bit);
}