#include <neopixel_Cwrapper.h>
#include <neopixel.h>


// C Wrapper for onionNeopixel class implementation

extern "C" {

onionNeopixel *neopixel = NULL;


void neopixelSetVerbosity(int verbosity)
{
	onionSetVerbosity(verbosity);
}

int	neopixelInit (int devAddr, int pin, int length)
{
	int 	status;

	// create the object
	neopixel 	= new onionNeopixel(devAddr);

	// setup the pin and length
	status 	=  neopixel->SetPin(pin);
	status 	|=  neopixel->SetLength(length);
	status 	|=  neopixel->Init();

	return status;
}

int neopixelSetBrightness (int brightness)
{
	int 	status;

	// set the brightness
	if (neopixel != NULL) {
		status 	= neopixel->SetBrightness(brightness);
	}

	return status;
}

int	neopixelSetPixel (int pixelId, int red, int green, int blue)
{
	int 	status;

	// setup the pixel
	if (neopixel != NULL) {
		status 	= neopixel->SetPixel(pixelId, red, green, blue);
	}

	return status;
}

int	neopixelSetBuffer (int *buf, int size)
{
	int 	status;

	// setup the buffer
	if (neopixel != NULL) {
		status 	= neopixel->SetBuffer(buf, size);
	}

	return status;
}

int	neopixelShowPixels ()
{
	int 	status;

	// show all pixels
	if (neopixel != NULL) {
		status 	= neopixel->ShowPixels();
	}

	return status;
}

void neopixelFree () 
{
	if (neopixel != NULL) {
		neopixel->CleanUp();
		delete neopixel;
	}
}


} 	// extern "C"
