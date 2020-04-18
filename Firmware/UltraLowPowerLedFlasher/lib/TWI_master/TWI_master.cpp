#include "TWI_master.h"

//Some C-style boilerplate
static bool i2c_start_cond(void);
static bool i2c_stop_cond(void);
static bool i2c_write_bit(bool bit);
static bool i2c_read_bit(void);
static void clear_SDA();
static void clear_SCL();
static void set_SDA();
static void set_SCL();
static bool read_SCL();
static bool read_SDA();
static void I2C_delay(void);
static const byte I2CSPEED = 10;
static bool started = false; // global data

TwiWire::TwiWire(/* args */)
{
}

/*! \brief initialize twi master mode
 */
void TwiWire::begin()
{
	set_SDA();
	set_SCL();
}

void TwiWire::beginTransmission(byte slaveAddress)
{
	this->slaveAddress = slaveAddress;
}

/*! \brief Writes data from buffer.
    \param indata Pointer to data buffer
    \param bytes  Number of bytes to transfer
    \return 1 if successful, otherwise 0
 */
bool TwiWire::writeEndTransmission(byte *indata, char bytes, bool stop)
{
	if (!i2c_write_byte(true, false, slaveAddress))
	{
		return false;
	}
	for (byte index = 0; index < bytes; index++)
	{
		if (!i2c_write_byte(false, (index + 1 == bytes) && stop, indata[index]))
		{
			return false;
		}
	}
	return true;
}

/*! \brief Reads data into buffer.
    \param data Pointer to data buffer
    \param bytes  Number of bytes to read
    \return 1 if successful, otherwise 0
 */
bool TwiWire::readRequestFrom(byte slaveAddress, byte *data, char bytes)
{
	this->slaveAddress = slaveAddress;
	i2c_write_byte(true, true, slaveAddress | 0x01);
	for (byte index = 0; index < bytes; index++)
	{
		if (!i2c_read_byte(index + 1 == bytes, index + 1 == bytes, data[index]))
		{
			return false;
		}
	}
	return true;
}

// Write a byte to I2C bus. Return 0 if ack by the slave.
bool TwiWire::i2c_write_byte(bool send_start, bool send_stop, byte data)
{
	bool ack;
	if (send_start)
	{
		i2c_start_cond();
	}
	for (byte bit = 0; bit < 8; ++bit)
	{
		i2c_write_bit((data & 0x80) != 0);
		data <<= 1;
	}
	ack = ~i2c_read_bit();
	if (send_stop)
	{
		i2c_stop_cond();
	}
	return ack;
}

// Read a byte from I2C bus
bool TwiWire::i2c_read_byte(bool nack, bool send_stop, byte &data)
{
	data = 0;
	for (byte bit = 0; bit < 8; ++bit)
	{
		data = (data << 1) | i2c_read_bit();
	}
	if (!i2c_write_bit(nack))
	{
		return false;
	}
	if (send_stop)
	{
		return i2c_stop_cond();
	}
	return true;
}

/*! \brief Sends start condition
 */
bool i2c_start_cond(void)
{
	if (started)
	{
		// if started, do a restart condition
		// set SDA to 1
		set_SDA();
		I2C_delay();
		set_SCL();
		while (read_SCL() == 0)
		{	// Clock stretching
			// You should add timeout to this loop
		}
		// Repeated start setup time, minimum 4.7us
		I2C_delay();
	}
	if (read_SDA() == 0)
	{
		//arbitration_lost();
		return false;
	}
	// SCL is high, set SDA from 1 to 0.
	clear_SDA();
	I2C_delay();
	clear_SCL();
	started = true;
	return true;
}

bool i2c_stop_cond(void)
{
	// set SDA to 0
	clear_SDA();
	I2C_delay();
	set_SCL();
	// Clock stretching
	while (read_SCL() == 0)
	{
		// add timeout to this loop.
	}
	// Stop bit setup time, minimum 4us
	I2C_delay();
	// SCL is high, set SDA from 0 to 1
	set_SDA();
	I2C_delay();
	if (read_SDA() == 0)
	{
		//arbitration_lost();
		return false;
	}
	started = false;
	return true;
}

// Write a bit to I2C bus
bool i2c_write_bit(bool bit)
{
	if (bit)
	{
		set_SDA();
	}
	else
	{
		clear_SDA();
	}
	// SDA change propagation delay
	I2C_delay();
	// Set SCL high to indicate a new valid SDA value is available
	set_SCL();
	// Wait for SDA value to be read by slave, minimum of 4us for standard mode
	I2C_delay();
	while (read_SCL() == 0)
	{	// Clock stretching
		// You should add timeout to this loop
	}
	// SCL is high, now data is valid
	// If SDA is high, check that nobody else is driving SDA
	if (bit && (read_SDA() == 0))
	{
		//arbitration_lost();
		return false;
	}
	// Clear the SCL to low in preparation for next change
	clear_SCL();
	return true;
}

// Read a bit from I2C bus

bool i2c_read_bit(void)
{
	bool bit;
	// Let the slave drive data
	set_SDA();
	// Wait for SDA value to be written by slave, minimum of 4us for standard mode
	I2C_delay();
	// Set SCL high to indicate a new valid SDA value is available
	set_SCL();
	while (read_SCL() == 0)
	{	// Clock stretching
		// You should add timeout to this loop
	}
	// Wait for SDA value to be written by slave, minimum of 4us for standard mode
	I2C_delay();
	// SCL is high, read out bit
	bit = read_SDA();
	// Set SCL low in preparation for next operation
	clear_SCL();
	return bit;
}

void I2C_delay(void)
{
	delayMicroseconds(5);
	// volatile int v;
	// int i;
	// for (i = 0; i < I2CSPEED / 2; ++i)
	// {
	// 	v;
	// }
}

void clear_SDA()
{
	bitClear(PORT_SDA, SDA);
	bitSet(DDR_SDA, SDA);
}

void clear_SCL()
{
	bitClear(PORT_SCL, SCL); //might be removed
	bitSet(DDR_SCL, SCL);
}

void set_SDA()
{
	bitClear(DDR_SDA, SDA);
}

void set_SCL()
{
	bitClear(DDR_SCL, SCL);
}

bool read_SCL()
{
	return bitRead(PIN_SCL, SCL);
}

bool read_SDA()
{
	return bitRead(PIN_SDA, SDA);
}