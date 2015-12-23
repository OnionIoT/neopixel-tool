#
# Copyright (C) 2015 Onion Corporation
# 
# Author: Lazar Demin  <lazar@onion.io>
#
# This is free software, licensed under the GNU General Public License v2.
#

from OmegaArduinoDock import neopixel
import time
import math	

# setup the neopixel class
NEOPIXEL_PIN 	= 6
NEOPIXEL_NUMBER	= 64

npixel 	= neopixel.OnionNeopixel(NEOPIXEL_PIN, NEOPIXEL_NUMBER)


# other functions
NUM_COLOURS 	= 7

# function to return r,g,b values for pre-specified colours based on an index
def getColours(idx):
	colourObj 	= {}

	if idx == 0:
		# magenta
		colourObj['r'] 	= 0xff
		colourObj['g'] 	= 0x00
		colourObj['b'] 	= 0xff
	elif idx == 1:
		# yellow
		colourObj['r'] 	= 0xff
		colourObj['g'] 	= 0xff
		colourObj['b'] 	= 0x00
	elif idx == 2:
		# aqua
		colourObj['r'] 	= 0x00
		colourObj['g'] 	= 0xff
		colourObj['b'] 	= 0xff
	elif idx == 3:
		# white
		colourObj['r'] 	= 0xff
		colourObj['g'] 	= 0xff
		colourObj['b'] 	= 0xff
	elif idx == 4:
		# red
		colourObj['r'] 	= 0xff
		colourObj['g'] 	= 0x00
		colourObj['b'] 	= 0x00
	elif idx == 5:
		# navy blye
		colourObj['r'] 	= 0x00
		colourObj['g'] 	= 0x32
		colourObj['b'] 	= 0xff
	elif idx == 6:
		# green
		colourObj['r'] 	= 0x00
		colourObj['g'] 	= 0xff
		colourObj['b'] 	= 0x14
	else:
		# ?
		colourObj['r'] 	= 0x11
		colourObj['g'] 	= 0x11
		colourObj['b'] 	= 0x11

	return colourObj


# function to find intermediate colour between two colours (based on a number of steps between the two colours)
def getIntermediateColours (colourCurrent, colourNext, colourStep, numColourSteps):
	colourDiff		= {}

	# find the difference between the two colours
	colourDiff['r'] 	= float(colourNext['r'] - colourCurrent['r']) / numColourSteps
	colourDiff['r']		= getRoundedNumber(colourDiff['r'])

	colourDiff['g'] 	= float(colourNext['g'] - colourCurrent['g']) / numColourSteps
	colourDiff['g']		= getRoundedNumber(colourDiff['g'])

	colourDiff['b'] 	= float(colourNext['b'] - colourCurrent['b']) / numColourSteps
	colourDiff['b']		= getRoundedNumber(colourDiff['b'])
	#print ' colourDiff: %d %d %d'%(colourDiff['r'], colourDiff['g'], colourDiff['b'])

	# find the colour based on the colourStep
	colourCurrent['r'] += int(colourDiff['r'] * colourStep)
	colourCurrent['g'] += int(colourDiff['g'] * colourStep)
	colourCurrent['b'] += int(colourDiff['b'] * colourStep)

	return colourCurrent

# function to round down for positive numbers and round down if a number is negative
def getRoundedNumber (number):
	ret = 0

	if number > 0:
		ret = math.floor(number)
	else:
		ret = math.ceil(number)

	return ret


# function to write a single colour to all pixels and then display
def writeToNeopixels (displayColour):
	for i in range(0, NEOPIXEL_NUMBER):
		ret = npixel.setPixel(i, displayColour['r'], displayColour['g'], displayColour['b'])

	ret = npixel.showPixels()

	return ret




## main program
# define program paramaters
colourSteps 	= 25
loopDelay0 		= 0.3
loopDelay1 		= loopDelay0 * 2.0

# outer infinite loop
print '> Starting colour loop...'
while 1:
	# loop through the colours
	for i in range(0, NUM_COLOURS):
		# sanitize the next colour
		next 	= i + 1
		if next == NUM_COLOURS:
			next = 0
		#print 'Colour id: ', i, ', next id is: ', next

		# loop through all steps
		for j in range(0, colourSteps):
			# get the current colour 
			currentCol 	= getColours(i)
			# get the next colour
			nextCol 	= getColours(next)
			# find the intermediate colour based on the current step
			displayCol 	= getIntermediateColours(currentCol, nextCol, j, colourSteps)

			# display the colour
			#print '   step %d, colour: 0x%02x%02x%02x'%(j, displayCol['r'], displayCol['g'], displayCol['b'])
			writeToNeopixels(displayCol)

			# delay between the colour steps
			time.sleep(loopDelay0)

		# delay between the colours
		time.sleep(loopDelay1)






