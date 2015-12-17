#include <neopixel.h>

onionNeopixel::onionNeopixel (int addr)
{
	Reset();

	// set up specifics
	devAddr		= addr;
}

onionNeopixel::~onionNeopixel (void)
{
	// nothing for now
}

void onionNeopixel::Reset ()
{
	// set up defaults
	devAddr 	= NEOPIXEL_I2C_DEVICE_ADDR;
	pin 		= 6;
	length 		= -1;

	buffer		= NULL;
}

int onionNeopixel::SetPin (int input)
{
	int 	status;

	// save the pin number
	pin 	= input;
	onionPrint(ONION_SEVERITY_INFO, "> Setting pin to %d\n", pin);

	// send the I2C command
	status	= i2c_writeBytes(	NEOPIXEL_I2C_DEVICE_NUM,
			 					devAddr, 
			 					ARDUINO_DOCK_ADDR_SET_NEOPIXEL_PIN, 
			 					pin, 
			 					1
			 				);

	return status;
}

int onionNeopixel::SetLength (int input)
{
	int 	status;

	// save the length
	length 	= input;
	onionPrint(ONION_SEVERITY_INFO, "> Setting strip length to %d\n", length);

	// send the I2C command
	status	= i2c_writeBytes(	NEOPIXEL_I2C_DEVICE_NUM,
			 					devAddr, 
			 					ARDUINO_DOCK_ADDR_SET_NEOPIXEL_STRIP_LENGTH, 
			 					length, 
			 					1
			 				);

	return status;
}

int onionNeopixel::SetColours (int *buf)
{
	int 	status, size, i;
	uint8_t	*buffer;

	// setup the buffer
	size 	= length * 3;
	onionPrint(ONION_SEVERITY_INFO, "> Sending colour buffer of length %d\n", size);

	// create a buffer for the i2c write
	buffer 	= new uint8_t[size+1];

	// populate the buffer
	buffer[0] 	= ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATA;	// i2c register address
	for (i = 0; i < size; i++) {
		buffer[i+1]	= (uint8_t)(buf[i]);
	}


	// send the I2C command
	status	= i2c_writeBuffer(	NEOPIXEL_I2C_DEVICE_NUM,
			 					devAddr, 
			 					ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATA, 
			 					buffer, 
			 					size+1
			 				);


	return status;
}