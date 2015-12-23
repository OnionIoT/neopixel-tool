#ifndef _ONION_NEOPIXEL_TOOL_H_
#define _ONION_NEOPIXEL_TOOL_H_

#include <module.h>

#include <onion-debug.h>
#include <onion-i2c.h>
		

#define NEOPIXEL_PRINT_BANNER			"neopixel-tool::"

#define NEOPIXEL_I2C_DEVICE_NUM			(0)
#define NEOPIXEL_I2C_DEVICE_ADDR		(0x08)

#define ARDUINO_DOCK_ADDR_NEOPIXEL_INIT				(0x20)
#define ARDUINO_DOCK_ADDR_SET_NEOPIXEL_PIN			(0x21)
#define ARDUINO_DOCK_ADDR_SET_NEOPIXEL_STRIP_LENGTH	(0x22)
#define ARDUINO_DOCK_ADDR_SET_NEOPIXEL_BRIGHTNESS	(0x26)
#define ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATA			(0x23)
#define ARDUINO_DOCK_ADDR_SET_NEOPIXEL_DATAPOINT	(0x24)
#define ARDUINO_DOCK_ADDR_SHOW_NEOPIXEL				(0x25)

#define NEOPIXEL_MAX_TRANSMISSION_PIXELS			9



class onionNeopixel : public Module {
public:
	onionNeopixel(int addr = NEOPIXEL_I2C_DEVICE_ADDR);
	~onionNeopixel(void);

	void	Reset			(void);

	int 	SetPin			(int input);
	int 	SetLength	 	(int input);
	int 	Init	 		();
	int 	Init	 		(int pin, int length);

	int 	SetBrightness 	(int input);
	
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
	int 	brightness;
	int* 	buffer;
};


#endif // _ONION_NEOPIXEL_TOOL_H_