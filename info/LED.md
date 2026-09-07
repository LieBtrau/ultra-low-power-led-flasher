# LED
## Scotopic Vision
Under low-light conditions, rod cells dominate and shift peak sensitivity to 507 nm.  The available LEDs on Digikey for this wavelength are all quite inefficient (< 100 lm/W).  Selecting the color "lime" instead yielded better results, as shown below.

## Original version
Uses [Luxeon 3535L L135-L567003500000](./LED/datasheet/DS146_LUXEON%203535L%20Color%20Line.pdf)
* 44 - 64 lm @ 100 mA
* Color : Lime
* Efficacy : 184 lm/W

Can in 2026 be upgraded to [Lumileds L128-LME1003500000](./LED/datasheet/DS236_LUXEON_2835-color-line.pdf) : 3535, 70 - 82 lm @ 120 mA

The 2026 version will use 2835 package, not 3535 because of the availability.

## 2026 version
* [Osram GW JTLPS1.1L-MKMP-NC-1-150-R33](./LED/datasheet/GW%20JTLPS1.1L_EN.pdf) : 2835, 96 - 116 lm @ 150 mA, 2.9 V - 3.3 V : 193 - 266 lm/W
  * large pad is cathode
  * corner marking on cathode
* [Cree JE2835APL-N-0001A0000-N0000001](./LED/datasheet/JSeries-2835-Color.pdf) : 2835, 90 - 105 lm @ 140 mA, 236 lm/W (datasheet)
  * large pad is cathode
  * corner marking on cathode

## LCSC LEDs
* C17637249 : 64 (@ 2.7 V)- 96 lm (@3.1V) @ 150 mA, 2835 : 153 lm/W
  * large pad is cathode
  * corner marking on cathode
* C2843870 : 4100 - 6000 mcd, 60 mA, 120°, 3.4 V, 2835 : 66 - 96 lm/W
* C2929613 : 1500 - 2500 mcd, 20 mA, 120°, 3.4 V, 2835 : 72 - 120 lm/W
  * symmetrical pads
* C49435720 : 8300 - 12000 mcd, 150 mA, 120°, 3.4 V, 2835 : 53 - 77 lm/W

From Osram LT CRBP.01 datasheet, 3.28 lm = 1 cd (more or less for a 120° LED)