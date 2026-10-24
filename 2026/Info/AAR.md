# Overview
Replace the light of an translucent bear with a very low power one.

# Goals and objectives
* Light should always be on.
* Light must be low power.
* Electronics must fit on existing battery compartment

# Analysis of outcomes
Light is functional after a few minor patches

# Analysis of the performance shown on critical tasks
* Light output is acceptable to my mind, but too bright for my wife, even at the 1.1 µA setting.
* Light output could not be controlled at will because the correct potentiometer had not been ordered.

## Current sensing
* The current measuring trick by adding a diode parallel to the sense resistor to keep voltage drop limited, has its shortcomings.  Even when there's very little voltage over the diode, it shunts current from the sense resistor and impacts the measurement.  Adding a second diode in series helps.  A device with a sharper turn-on would be more suitable.
* The current sense resistor was too large, causing a too large voltage drop.

# Summary
Overall successful project

# Recommendations
* Check the BoM in detail to see what is in stock and what should be ordered.
* For the current measurement with a parallel diode : add two diodes in series and dimension the current sense resistor so that it drops less than 200 mV at the highest current consumption.

Currently the light output is set so that the device consumes 1.1 µA.  For my wife it's still too bright, so the light has been donated to my daughter.

