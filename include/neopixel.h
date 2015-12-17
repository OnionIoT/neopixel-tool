#ifndef _ONION_NEOPIXEL_TOOL_H_
#define _ONION_NEOPIXEL_TOOL_H_

#include <module.h>

#include <onion-debug.h>
#include <onion-i2c.h>
		

#define NEOPIXEL_PRINT_BANNER			"ADS1X15::"

#define NEOPIXEL_I2C_DEVICE_NUM			(0)
#define NEOPIXEL_I2C_DEVICE_ADDR		(0x08)

#define ARDUINO_DOCK_ADDR_SET_NEOPIXEL_PIN			(0x20)
#define ARDUINO_DOCK_ADDR_SET_NEOPIXEL_STRIP_LENGTH	(0x21)
#define ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATA			(0x22)
#define ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATAPOINT	(0x23)
#define ARDUINO_DOCK_ADDR_SHOW_NEOPIXEL				(0x24)

#define NEOPIXEL_MAX_TRANSMISSION_PIXELS			9



class onionNeopixel : public Module {
public:
	onionNeopixel(int addr = NEOPIXEL_I2C_DEVICE_ADDR);
	~onionNeopixel(void);

	void	Reset			(void);

	int 	SetPin			(int input);
	int 	SetLength	 	(int input);
	
	int 	SetPixel 		(int pixelId, int red, int green, int blue);
	int 	SetBuffer 		(int *buf, int size);

	int 	ShowPixels		();


private:
	// private functions
	int 	_WriteBuffer	(int size, int overhead, int numPixels, int* inputBuffer);


	// private members
	int 	devAddr;
	int 	pin;
	int 	length;
	int* 	buffer;
};


#endif // _ONION_NEOPIXEL_TOOL_H_