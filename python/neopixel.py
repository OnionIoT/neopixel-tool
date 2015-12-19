from ctypes import *
from array import array

libneopixel = CDLL("libonionneopixel.so") 

EXIT_SUCCESS 	= 0
EXIT_FAILURE	= 1

ARDUINO_DOCK_DEVNUM		= 0
ARDUINO_DOCK_DEVADDR	= 0x08


class OnionNeopixel:
	""" Class for programming Neopixels via the Arduino Dock"""

	def __init__(self, pin, length, deviceAddr = ARDUINO_DOCK_DEVADDR, deviceNum = ARDUINO_DOCK_DEVNUM):
		# store the device number and device address
		self.devNum 		= deviceNum;
		self.devAddr 		= deviceAddr;

		self.pin 			= pin
		self.pixels 		= length

		self.init 			= 0

		libneopixel.neopixelSetVerbosity(2)

		# initialize the C
		#if libneopixel.neopixelInit(self.devAddr, self.pin, self.pixels) == EXIT_SUCCESS:
		if libneopixel.neopixelInit(self.pin, self.pixels) == EXIT_SUCCESS:
			self.init = 1


	def setPixel (self, pixelId, red, green, blue):
		""" Set a specific pixel to the specified colour pattern """
		if self.init == 0:
			return -1

		# make the c call
		if libneopixel.neopixelSetPixel(pixelId, red, green, blue) == EXIT_SUCCESS:
			return 0

		return 1

	def setBuffer (self, pyBuf):
		""" Set a buffer of colours """

		# print the contents of the python list
		#for i in range(0, size):
		#	print 'pyBuf[%d] = 0x%02x'%(i, pyBuf[i])

		# find the length of the python list
		size 		= len(pyBuf)

		# create an array for use with C
		cArrType 	= c_int * (size)
		cArr 		= cArrType()

		# populate C array with python list contents
		for i in range(0, size):
			cArr[i] 	= pyBuf[i]
			#print 'cArr[%d] = 0x%02x'%(i, cArr[i])

		# make the c call
		if libneopixel.neopixelSetBuffer(cArr, size) == EXIT_SUCCESS:
			return 0

		return 1


	def showPixels (self):
		""" Display all saved pixels on the neopixel display """
		if self.init == 0:
			return -1

		# make the c call
		if libneopixel.neopixelShowPixels() == EXIT_SUCCESS:
			return 0

		return 1

