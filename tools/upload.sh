#!/bin/sh

## Copy the example python code to downloads.onion.io/arduino-dock

aws s3 cp examples/slowColourChange.py s3://onion-downloads/arduino-dock/slowColourChange.py

