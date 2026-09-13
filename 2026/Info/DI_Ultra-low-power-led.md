Design Ideas
---
# How much light is needed?
The effect should be like "glow-in-the-dark" effect.  Measurements using the existing [Ultra low power LED](https://hackaday.io/project/169882-ultra-low-power-led) showed that pulse width should be at least 2 µs.  5 µs could still be acceptable.  20 µs would be maximum.  I guess it all depends on the preferences of individual users.  So let's make the pulse width easily adjustable, e.g. using a potentiometer.

# Testing
## Light output
VEML7700 and TSL2591 light sensor are available.  TSL2591 has a higher resolution and doesn't suffer from the repeated start issue as documented in [my earlier work](https://hackaday.io/page/6590-ambient-light-sensing).

# References
* [Yet another ultra low power LED](https://hackaday.io/project/203844-yet-another-ultra-low-power-led)
* [Ultra low power LED](https://hackaday.io/project/169882-ultra-low-power-led)