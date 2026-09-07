# Output transistor
| Parameter | Original version | 2026-A      | 2026-B    |
|-----------|------------------|-------------|-----------|
| MPN       | Infineon BSS806N| Diodes DMG1012T-7  | Diodes DMN2310UT |
| Qg [nC]   | 1.7              | 0.7         | 0.7       |
| Vgs_th [V]| 0.55             | 0.5 - 1.0   | 0.45 - 0.95|
| rds_on @ 1.8 V [mOhm]| 82    | 500 - 700   | 263 - 400 |
| I_GSS [µA]| 8                | 0.1         | 1.0      |
| I_DSS [µA]| 1                | 1          | 10        |
|Package    | SOT23-3          | SOT523     | SOT523    |

BSS806NE variant has an Igss of 6 µA.  It doesn't really matter much in this application because the duty cycle is very low.
Gate current can be reduced with a 10 ohm gate resistor