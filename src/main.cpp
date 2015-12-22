#include <main.h>

void usage(const char* progName) {
	printf("Utility to control Neopixels with the Arduino Dock\n");
	printf("\n");

	printf("Usage:\n");
	printf("    %s -i -p <data pin> -l <number of neopixels>\n", progName);
	printf("Initialize the Arduino Dock to use Neopixels\n");
	printf("  <data pin>             Arduino Dock pin connected to Neopixel data pin\n");
	printf("  <number of neopixels>  Total number of neopixels to be controlled\n");
	printf("\n");

	printf("Usage:\n");
	printf("    %s [-s] set <pixel> <colour value>\n", progName);
	printf("Set the colour value of an individual pixel\n");
	printf("  <pixel>          Pixel number in the Neopixel strip/array\n");
	printf("  <colour value>   Hex colour value with 8 bits for each colour component (0xRRGGBB)\n");
	printf("Options\n");
	printf("  -s	Immediately display the colour change, otherwise it will be queued up\n");
	printf("\n");

	printf("Usage:\n");
	printf("    %s [-s] buffer <colour value string>\n", progName);
	printf("Set the colour value of a number of pixels\n");
	printf("  <colour value string>  Colour values of each pixel\n");
	printf("     ex:  010203040506 will set pixel 0 to 0x010203 and pixel 1 to 0x040506\n");
	printf("Options\n");
	printf("  -s	Immediately display the colour change, otherwise it will be queued up\n");
	printf("\n");

	printf("Usage:\n");
	printf("    %s -s\n", progName);
	printf("Display any queued colour changes\n");
	printf("\n");

	printf("\n");
}

int main(int argc, char* argv[])
{
	int 		status;
	int 		value;

	const char 	*progname;
	int 		verbose, debug;
	int 		ch;

	char		*val	= NULL;
	int 		cmdId, pixelId, pin, length, i, showPixels;
	int 		red, blue, green;

	int 		*buffer;
	onionNeopixel*	neopixelObj	= new onionNeopixel;


	// save the program name
	progname 	= argv[0];	

	// set the defaults
	verbose 	= ONION_VERBOSITY_NORMAL;
	//debug 		= ADS1X15_MAIN_DEFAULT_DEBUG;
	cmdId 		= -1;
	showPixels 	= 0;
	pin 		= NEOPIXEL_APP_DEFAULT_PIN;
	length 		= NEOPIXEL_APP_DEFAULT_LENGTH;


	//// parse the option arguments
	while ((ch = getopt(argc, argv, "vqdhisp:l:")) != -1) {
		switch (ch) {
		case 'v':
			// verbose output
			verbose++;
			break;
		case 'q':
			// quiet output
			verbose = ONION_VERBOSITY_NONE;
			break;
		case 'd':
			// debug mode
			debug 	= 1;
			break;
		case 'i':
			// init mode
			cmdId 	= NEOPIXEL_APP_CMD_ID_INIT;
			break;
		case 's':
			// show pixels
			showPixels 	= 1;
			break;
		case 'p':
			// set the pin
			pin 	= atoi(optarg);
			break;
		case 'l':
			// set the length
			length 	= atoi(optarg);
			break;
		default:
			usage(progname);
			return 0;
		}
	}

	// set the verbosity
	onionSetVerbosity(verbose);

	// advance past the option arguments
	argc 	-= optind;
	argv	+= optind;

	
	//// parse the arguments
	if (argc > 0) {		
		val 	= new char[1024];
		onionPrint(ONION_SEVERITY_DEBUG, ">> argument count is %d\n", argc);

		if (strcmp(NEOPIXEL_APP_CMD_PIXEL, argv[0]) == 0 ) {
			cmdId 	= NEOPIXEL_APP_CMD_ID_PIXEL;

			// read the pixelId, and colour component arguments
			if (argc > 1) {
				pixelId		= atoi(argv[1]);

				// parse the pixels
				sscanf(argv[2], "%2x%2x%2x", &red, &green, &blue);
				onionPrint(ONION_SEVERITY_DEBUG, ">> Read pixel colours from %s: r = %d, g = %d, b = %d\n", argv[2], red, green, blue);
			}
		}
		else if (strcmp(NEOPIXEL_APP_CMD_BUFFER, argv[0]) == 0 ) {
			cmdId 	= NEOPIXEL_APP_CMD_ID_BUFFER;

			// read the buffer
			if (argc > 1) {
				// find length of string buffer
				length 	= strlen(argv[1]);
				buffer 	= new int[length/2];	// initialize the int buffer
				
				// convert to int buffer
				for (i = 0; i < length; i += 2) {
					sscanf(argv[1] + i, "%2x", &(buffer[i/2]) );
					onionPrint(ONION_SEVERITY_DEBUG_EXTRA, ">>> set buffer[%d] to 0x%02x\n", i/2, buffer[i/2]);
				}

				onionPrint(ONION_SEVERITY_DEBUG, ">> input string length is %d, buffer length is %d\n", length, length/2);
				length 	/= 2;	// now represents size of int buffer
			}
			else {
				onionPrint(ONION_SEVERITY_FATAL, "ERROR: Expecting argument with buffer!\n");
				status 	= EXIT_FAILURE;
			}
		}
	}
	
	if (cmdId == -1 && showPixels == 0) {
		usage(progname);
		return EXIT_FAILURE;
	}



	//// actual program
	if (cmdId == NEOPIXEL_APP_CMD_ID_INIT) {
		onionPrint(ONION_SEVERITY_INFO, "> Initializing strip of length %d on pin %d\n", length, pin);
		status =  neopixelObj->SetPin(pin);	
		status |= neopixelObj->SetLength(length);
		status |= neopixelObj->Init();
	}
	else if (cmdId == NEOPIXEL_APP_CMD_ID_PIXEL) {
		onionPrint(ONION_SEVERITY_INFO, "> Setting pixel %d to 0x%02x%02x%02x\n",  pixelId, red, green, blue);
		status 	= neopixelObj->SetPixel(pixelId, red, green, blue);
	}
	else if (cmdId == NEOPIXEL_APP_CMD_ID_BUFFER) {
		onionPrint(ONION_SEVERITY_INFO, "> Writing buffer to strip\n");
		status 	= neopixelObj->SetBuffer(buffer, length);
	} 

	if (status == EXIT_FAILURE) {
		onionPrint(ONION_SEVERITY_INFO, "> Operation failed!\n");
	}

	if (showPixels == 1) {
		onionPrint(ONION_SEVERITY_INFO, "> Displaying pixels on strip\n");
		status 	= neopixelObj->ShowPixels();
	}


	return 0;
}