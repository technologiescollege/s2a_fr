__author__ = 'Copyright (c) 2014 Alan Yorinks All rights reserved.'

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

You should have received a copy of the GNU General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA


This file demonstrates how to use some of the basic PyMata operations
"""


from PyMata.pymata import PyMata
import time

# Create an instance of PyMata.
firmata = PyMata("/dev/ttyACM0")

# send the arduino a firmata reset
firmata.reset()

# configure the stepper to use pins 9.10,11,12 and specify 512 steps per revolution
firmata.stepper_config( 512, [12, 11, 10, 9])

# allow time for config to complete
time.sleep(.5)

# ask Arduino to return the stepper library version number to PyMata
firmata.stepper_request_library_version()

# allow time for command and reply to go across the serial link
time.sleep(.5)

print "Stepper Library Version",
print firmata.get_stepper_version()

# move motor #0 500 steps forward at a speed of 20
firmata.stepper_step(20, 500)

# move motor #0 500 steps reverse at a speed of 20
firmata.stepper_step(20, -500)

# close firmata
firmata.close()

