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

int onionNeopixel::SetBuffer (int *buf, int size)
{
	int 	status, i, overhead;
	uint8_t	*buffer;

	onionPrint(ONION_SEVERITY_INFO, "> Sending colour buffer of length %d\n", size);

	// adjust buffer size
	overhead	= 3; 	// 3 bytes of overhead (addr, number of pixels being sent, starting address to write the buffer)

	// create a buffer for the i2c write
	buffer 	= new uint8_t[size+overhead];

	// populate the buffer
	buffer[0] 	= ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATA;	// i2c register address
	buffer[1]	= size/3;			// number of pixels being sent
	buffer[2]	= 0;				// starting index of pixel
	for (i = 0; i < size; i++) {
		buffer[i+3]	= (uint8_t)(buf[i]);
	}


	// send the I2C command
	status	= i2c_writeBuffer(	NEOPIXEL_I2C_DEVICE_NUM,
			 					devAddr, 
			 					ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATA, 
			 					buffer, 
			 					size+overhead
			 				);


	return status;
}

int onionNeopixel::SetPixel (int pixelId, int red, int green, int blue)
{
	int 	status, size;
	uint8_t	*buffer;

	// create a buffer for the i2c write
	size	= 5;	// addr, pixel id, 3x colours
	buffer 	= new uint8_t[5];

	// populate the buffer
	buffer[0] 	= ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATAPOINT;	// i2c register address
	buffer[1]	= pixelId;	// pixel id
	buffer[2]	= red;		// r data
	buffer[3]	= green;	// g data
	buffer[4]	= blue;		// b data

	// send the I2C command
	status	= i2c_writeBuffer(	NEOPIXEL_I2C_DEVICE_NUM,
			 					devAddr, 
			 					ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATAPOINT, 
			 					buffer, 
			 					size
			 				);

	return status;
}

int onionNeopixel::ShowPixels ()
{
	int 	status;

	// send the I2C command to show the stored pixels
	status	= i2c_writeBytes(	NEOPIXEL_I2C_DEVICE_NUM,
			 					devAddr, 
			 					ARDUINO_DOCK_ADDR_SHOW_NEOPIXEL, 
			 					1, 
			 					1
			 				);

	return status;
}

