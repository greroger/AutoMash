# AutoMash
Attempt at semi automated homebrew control system using Raspberry Pi and Arduino

Working on a semi automated homebrew beer control system.
Using a Raspberry Pi 3 and QT 5.8 for the GUI and central control.

Will use Arduino for local PID controls on pumps and RIMS tube.

I2C to provide communication between Raspberry Pi and Arduino's.

Working on Arduino PID TRIAC phase control of pump's and heater.

Heater will be straight pid temperature control.

Pumps will use Hall effect flow sensor for pid control of flow rate.
Also add option of temperature controled flow rate for counter flow chiller.
