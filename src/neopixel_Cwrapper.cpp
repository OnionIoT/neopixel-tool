#include <neopixel_Cwrapper.h>
#include <neopixel.h>


// C Wrapper for onionNeopixel class implementation

extern "C" {

onionNeopixel *neopixel = NULL;


void neopixelSetVerbosity(int verbosity)
{
	onionSetVerbosity(verbosity);
}

int	neopixelInit (int pin, int length)
{
	int 	status;

	// create the object
	neopixel 	= new onionNeopixel();

	// setup the pin and length
	neopixel->SetPin(pin);
	neopixel->SetLength(length);

	return status;
}

int	neopixelSetPixel (int pixelId, int red, int green, int blue)
{
	int 	status;

	// setup the pixel
	if (neopixel != NULL) {
		neopixel->SetPixel(pixelId, red, green, blue);
	}

	return status;
}

int	neopixelSetBuffer (int *buf, int size)
{
	int 	status;

	// setup the buffer
	if (neopixel != NULL) {
		neopixel->SetBuffer(buf, size);
	}

	return status;
}

int	neopixelShowPixels ()
{
	int 	status;

	// show all pixels
	if (neopixel != NULL) {
		neopixel->ShowPixels();
	}

	return status;
}

void neopixelFree () 
{
	if (neopixel != NULL) {
		delete neopixel;
	}
}


} 	// extern "C"
