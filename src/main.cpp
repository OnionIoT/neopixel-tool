#include <neopixel.h>

void usage(const char* progName) {
	printf("Usage:\n");
	printf("\t%s [-qvd] <channel> [max voltage]\n", progName);
	printf("\n");
	printf("<channel>\tAnalog input channel, can be 0 to 3\n");
	printf("[max voltage]\tOptional: Set maximum expected input voltage\n");
	printf("\tmax:	 6.144 V\n");
	printf("\tmin: 	 0.256 V\n");
	printf("\tdefault: 6.144 V\n");
	printf("\n");
	printf("Options\n");
	printf("\t-q	Quiet: no output\n");
	printf("\t-v	Verbose: debug output\n");
	printf("\t-x	Extra Verbose: all debug output\n");
	printf("\t-d	Debug: do not carry out any I2C transactions\n");
	printf("\n");
}

int main(int argc, char* argv[])
{
	int 		status;
	int 		value;

	const char 	*progname;
	int 		verbose, debug;
	int 		ch;

	int 		pin	= -1;
	int 		length 	= -1;
	uint8_t		*buffer;
	onionNeopixel*	neopixelObj	= new onionNeopixel;

	// save the program name
	progname 	= argv[0];	

	// set the defaults
	verbose 	= ONION_VERBOSITY_NORMAL;
	//debug 		= ADS1X15_MAIN_DEFAULT_DEBUG;


	//// parse the option arguments
	while ((ch = getopt(argc, argv, "xvqdh")) != -1) {
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
		default:
			usage(progname);
			return 0;
		}
	}

	// advance past the option arguments
	argc 	-= optind;
	argv	+= optind;

	
	//// parse the arguments
	/*// pin argument
	if (argc > 0) {
		channel 	= atoi(argv[0]);

		if (channel < 0 || channel > ADS1X15_NUM_CHANNELS) {
			usage(progname);
			printf ("ERROR: invalid number of channels!\n");
			return EXIT_FAILURE;
		}
	}
	else {
		usage(progname);
		return EXIT_FAILURE;
	}

	// gain argument
	if (argc > 1) {
		gain 		= adsObj->ReadMaxVoltage( atof(argv[1]) );
		printf ("> Max input voltage %0.3f V corresponds to gain setting of %d\n", atof(argv[1]), gain);

		if (gain < 0 || gain > ADS1X15_NUM_GAIN) {
			usage(progname);
			printf ("ERROR: invalid max input voltage!\n");
			return EXIT_FAILURE;
		}
	}*/


	//// actual program
	onionSetVerbosity(verbose);

	neopixelObj->SetPin(6);

	length 	= 2;
	neopixelObj->SetLength(length);

	buffer 	= new uint8_t[length*3];
	buffer[0] 	= 0x00;
	buffer[1] 	= 0x00;
	buffer[2] 	= 0xff;

	buffer[3] 	= 0x00;
	buffer[4] 	= 0xff;
	buffer[5] 	= 0x00;

	neopixelObj->SetColours(buffer);


	return 0;
}