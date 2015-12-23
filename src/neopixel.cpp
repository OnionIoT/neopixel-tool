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

// set Arduino Dock output pin for Neopixel Data 
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

// set length of the strip
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

// initialize the neopixel display
int onionNeopixel::Init ()
{
	int 	status;

	onionPrint(ONION_SEVERITY_DEBUG, "> Initializing the neopixels\n", pin);

	// send the I2C command
	status	= i2c_writeBytes(	NEOPIXEL_I2C_DEVICE_NUM,
			 					devAddr, 
			 					ARDUINO_DOCK_ADDR_NEOPIXEL_INIT, 
			 					0x01, 
			 					1
			 				);

	return status;
}

// overloaded function that takes in the pin, length, and performs the init
int onionNeopixel::Init (int pin, int length)
{
	int 	status;

	status 	=  SetPin(pin);
	status 	|= SetLength(length);
	status	|= Init();

	return status;
}

int onionNeopixel::SetBuffer (int *buf, int size)
{
	int 	status, i, overhead, bufferSize, startIndex;
	uint8_t	*buffer;

	onionPrint(ONION_SEVERITY_INFO, "> Sending colour buffer of length %d\n", size);

	// check input size
	if (size % 3 != 0) {
		// need three bytes for each pixe;
		return EXIT_FAILURE;
	}

	// defaults
	overhead	= 3; 			// 3 bytes of overhead (addr, number of pixels being sent, starting pixel address to write the buffer)
	startIndex	= 0;
	

	// write the buffer via i2c
	//	note: maximum transmission size is 32 bytes, 
	//		so if buffer is for more than 9 pixels, will need multiple transmissions
	while (size > 0) {
		// find transmission size
		if (size/3 > NEOPIXEL_MAX_TRANSMISSION_PIXELS ) {
			bufferSize 	= NEOPIXEL_MAX_TRANSMISSION_PIXELS*3 + overhead;
			//onionPrint(ONION_SEVERITY_DEBUG_EXTRA, ">>> Transmitting maximum number of pixels, remaining size is %d\n", size);
		}
		else {
			bufferSize 	= size + overhead;
		}

		// perform the transmission
		_WriteBuffer(bufferSize, overhead, startIndex, buf);

		// adjust the overall size of the input buffer based on this transmission
		size 		-= bufferSize - overhead;
		// adjust the next starting index 
		//	always increment by max number of pixels (loop will only run again if max pixels are being sent)
		startIndex	+= NEOPIXEL_MAX_TRANSMISSION_PIXELS;
	}


	return status;
}

int onionNeopixel::_WriteBuffer(int size, int overhead, int startIndex, int* inputBuffer)
{
	int 	status, i;
	uint8_t	*buffer;

	// create a buffer for the i2c write
	buffer 	= new uint8_t[size];

	// populate the buffer
	buffer[0] 	= ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATA;	// i2c register address
	buffer[1]	= (size-overhead)/3;	// number of pixels being sent
	buffer[2]	= startIndex;			// starting index of pixel
	for (i = 0; i < size; i++) {
		buffer[i+3]	= (uint8_t)(inputBuffer[i+startIndex*3]);
	}


	// send the I2C command
	status	= i2c_writeBuffer(	NEOPIXEL_I2C_DEVICE_NUM,
			 					devAddr, 
			 					ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATA, 
			 					buffer, 
			 					size
			 				);

	// clean-up 
	delete buffer;

	return status;
}

int onionNeopixel::SetPixel (int pixelId, int red, int green, int blue)
{
	int 	status, size;
	uint8_t	*buffer;

	onionPrint(ONION_SEVERITY_DEBUG, "> Setting pixel %d\n", pixelId);

	// create a buffer for the i2c write
	size	= 5;	// addr, pixel id, 3x colours
	buffer 	= new uint8_t[size];

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

	// clean-up 
	delete buffer;

	return status;
}

int onionNeopixel::ShowPixels ()
{
	int 	status;

	onionPrint(ONION_SEVERITY_DEBUG, "> Displaying colours on neopixels\n");

	// send the I2C command to show the stored pixels
	status	= i2c_writeBytes(	NEOPIXEL_I2C_DEVICE_NUM,
			 					devAddr, 
			 					ARDUINO_DOCK_ADDR_SHOW_NEOPIXEL, 
			 					1, 
			 					1
			 				);

	return status;
}

