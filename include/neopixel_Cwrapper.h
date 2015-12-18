#ifndef _C_ONION_NEOPIXEL_TOOL_H_
#define _C_ONION_NEOPIXEL_TOOL_H_


// C Wrapper for onionNeopixel class

#ifdef __cplusplus
extern "C" {
#endif

void 	neopixelSetVerbosity	(int verbosity);
int		neopixelInit			(int pin, int length);

int		neopixelSetPixel		(int pixelId, int red, int green, int blue);
int		neopixelSetBuffer		(int *buf, int size);

int		neopixelShowPixels		();

void 	neopixelFree 			();


#ifdef __cplusplus
}
#endif

#endif // _C_ONION_NEOPIXEL_TOOL_H_