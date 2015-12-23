#include <neopixel.h>

#define NEOPIXEL_APP_DEFAULT_PIN		(6)
#define NEOPIXEL_APP_DEFAULT_LENGTH		(32)

#define NEOPIXEL_APP_CMD_PIXEL			"set"
#define NEOPIXEL_APP_CMD_BUFFER			"buffer"

#define NEOPIXEL_APP_CMD_ID_NONE		-1
#define NEOPIXEL_APP_CMD_ID_INIT		0
#define NEOPIXEL_APP_CMD_ID_PIXEL		1
#define NEOPIXEL_APP_CMD_ID_BUFFER		2


void 	usage		(const char* progName);