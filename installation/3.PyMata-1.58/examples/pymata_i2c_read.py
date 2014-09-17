__author__ = 'Copyright (c) 2013 Alan Yorinks All rights reserved.'

"""
Copyright (c) 2013 Alan Yorinks All rights reserved.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU  General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.

You should have received a copy of the GNU  General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


This file demonstrates using PyMata to read temperature values from a SparkFun Digital Temperature Sensor
Breakout for the TMP102 device - SparkFun part #SEN-11931

The code is based on a bildr article: http://bildr.org/2011/01/tmp102-arduino/
"""

# import the API class
import time

from PyMata.pymata import PyMata



# The PyMata constructor will print status to the console and will return
# when PyMata is ready to accept commands or will exit if unsuccessful
firmata = PyMata("/dev/ttyACM0")

#configure the I2C pins. This code is for the UNO

firmata.i2c_config(0, firmata.ANALOG, 4, 5)

# read i2c device at address 0x48, with no register specified. Expect 2 bytes to be returned
# and the operation is a single shot read
firmata.i2c_read(0x48, 0, 2, firmata.I2C_READ)

# give the serial interface time to send a read, for the device to execute the read
# and to get things back across the interface
time.sleep(3)

# retrieve the data sent from device
data = firmata.i2c_get_read_data(0x48)

# do some calculations on the raw data returned
TemperatureSum = (data[1] << 8 | data[2]) >> 4

celsius = TemperatureSum * 0.0625
print celsius

fahrenheit = (1.8 * celsius) + 32
print fahrenheit

firmata.close()
