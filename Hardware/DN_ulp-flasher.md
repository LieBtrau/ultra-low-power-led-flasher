# Purpose of the design
Provide a "glow-in-the-dark" like light with the translucent bear from Livarno as sold by Lidl retail shop.

# Power input circuit
The circuit is powered by 3 x AA cells, of which only two will be used.  The remaining battery contacts (on 1.5 V and 4.5 V) will be used as solder connection for mechanical rigidity only.

# Input current measurement
Current consumption can be measured by measuring voltage over R12.  To reduce power drop at power up (will there be one?), a diode D4 is placed in parallel with R12.

# Input reverse polarity protection
A PMOS has a much lower voltage drop than a diode.  It doesn't provide reverse current protection however, but that's not relevant in this application.

# 1V8 power supply
The one-shot timer consumes less when it operates on a lower voltage level.  The lowest allowable voltage is 1.65 V.  A 1.8 V regulator still has some margin.  The TPS7A02 has a very low quiescent current.

More details on [LDO](../info/LDO.md).

# Oscillator
The oscillator consumes less current when it operates on a lower voltage level.  D1 and D3 are used to lower the operating voltage.  Care has to be taken that the output levels on the collector of Q2 are still outside U1./A's schmitt-trigger hysteresis zone.  The collector of Q2 has to rise to at least 1.2 V.  

C1 reduces power supply impedance for the high frequency pulses.  It considerably reduces the ripple at the cathode of D3.

The [original circuit](http://www.discovercircuits.com/H-Corner/Ultra%20low%20current%20oscillator.htm) has been adjusted to allow operation at a lower power supply.  By increasing the ratio of R4+R5 / R7, the base of Q3 now sits by default at a lower level.  

The very large resistor values have been reduced to 10 M.  Making series and parallel combinations reduces the number of different components in the BoM.

C5 has been tuned to set the output frequency as low as possible while avoiding LED flicker.  That frequency is somewhere around 50 Hz.

# One-shot timer
The pulse width of the oscillator isn't very well controlled.  The oscillator is used to trigger a one-shot timer where pulse width can be tightly controlled.

The one-shot timer is wired to create a positive pulse on the falling edge of /A.  RV1 allows to adjust the pulse width from 2 µs to 20 µs.  These pulse widths are empirically determined to cause the desired "glow-in-the-dark" light effect.  

R14 allows to connect U1.6 to GND, which might be needed for some versions of the 74LVC1G123.

C6 provides local power supply decoupling.

More details on [one-shot-timer](../info/one-shot-timer.ipynb).

# NMOS switch
R9 is added as gate resistor to limit the in-rush current in the gate of Q4/Q5.  For debugging, R9 can be removed and R13 can be placed instead.

Two different footprints for the NMOS have been added.  That allows for evaluation of different parts.

The sense resistor in series with the drain allows for measuring the current through the NMOS.  Because the voltages over the resistor will be very low and high speed, a 51 source resistor has been added.  Set the oscilloscope in 50 ohm mode to measure.  Keep in mind the 3dB attenuation of the impedance match.

More details on [switching element](../info/switching_element.md)

# Inductor
When the NMOS stops conducting, the collapsing magnetic field causes the LED to conduct.  Some simulations have been done to determine the ideal ESR.  Inductors with very low ESR are typically too bulky.  Very small inductors have a large ESR.  ESR values in the range of a few ohms are typically acceptable.

To avoid blocking the light, don't place the inductor too close to the LED.

# LED
Turns electrical energy into optical energy.  More details on [LED](../info/LED.md).