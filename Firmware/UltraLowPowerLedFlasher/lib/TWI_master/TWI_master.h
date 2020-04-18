#pragma once
#include <Arduino.h>
/*! \brief Definition of pin used as SCL. */
const byte SCL = PB3;

/*! \brief Definition of pin used as SDA. */
const byte SDA = PB4;

/*! \brief Definition of PORT used as SCL. */
#define PORT_SCL PORTB
/*! \brief Definition of DDR used as SCL. */
#define DDR_SCL DDRB
/*! \brief Definition of PIN used as SCL. */
#define PIN_SCL PINB
/*! \brief Definition of PORT used as SDA. */
#define PORT_SDA PORTB
/*! \brief Definition of DDR used as SDA. */
#define DDR_SDA DDRB
/*! \brief Definition of PIN used as SDA. */
#define PIN_SDA PINB

#define SET_SDA_OUT() DDR_SDA |= (1 << SDA)
#define SET_SDA_IN() DDR_SDA &= ~(1 << SDA)

/*! \brief Delay used to generate clock */
#define DELAY 2

/*! \brief Delay used for STOP condition */
#define SCL_SDA_DELAY 1

class TwiWire
{
public:
    TwiWire(/* args */);
    void begin();
    void beginTransmission(byte slaveAddress);
    bool writeEndTransmission(byte *data, char bytes, bool stop);
    bool readRequestFrom(byte slaveAddress, byte *data, char bytes);

private:
    const byte WRITE = 0;
    const byte READ = 1;
    byte slaveAddress; /*! \brief Slave 8 bit address (bits 7 down 1). */
    bool i2c_write_byte(bool send_start, bool send_stop, byte data);
    bool i2c_read_byte(bool nack, bool send_stop, byte& data);
};
