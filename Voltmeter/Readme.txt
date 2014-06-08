This project uses the AVR ATmega168 to produce a very accurate voltage meter, for use in testing battery voltages.
The project also makes use of a technique called over-sampling.
In order to use this project you have to take initial measurements of your voltage divider set-up: (1) take the total resistance and divide it the average resistance.
(2) Also take the current measurement of the voltage of the battery which you will use in experimentation.
In the voltmeter.c code, set REF_VCC = the power supply voltage used to power the AVR. and set VOLTAGE_DIV_FACTOR = the result of (1).