# Parts:

| Qty | Part |
| --- | ---- |
| 1 | Raspberry Pi 3 |
| 1 | Touchscreen |
| 3 | ATmega328P |
|   | RTD Amp |
|   | P100 RTD 1/2" NTP 4" probe |
| 1 | Triac for heater |
| 2 | Triac for motors |
|   | RIMS tube |
|   | Heater element |
| 2 | Burners, probably Banjo, maybe Blickmann |
|   | Looks like the Anvil burners might be a good choice |
|   | Superstrut stuff |
| 3 | 10 gal pots |
|   | Enclosure for pi that holds touchscreen |
|   | Ninjaflex to make gasket to hold touchscreen |
| 2 | Beer pumps, probably march |
| 2 | Flow meters |

# Notes:
Plan Looking at using a raspberry pi 3 for the compute hub with a touchscreen
display and maybe a rotary encoder and a couple of switches to help with the
interface. Then using the ATmega chips for doing the pid work.

The pid's for the pumps and heater will use Triacs and zero crossing pwm. Will
need the opto-isolaters and some other parts to do the hookup. The existing pid
and zero crossing libraries should work fine for what I need.

Going to be looking at using superstrut material from big box stores for the
frame.

Be using 2 burners initially one for boil one for the HLT.

Will have main 220 drier line coming into the control box with outlets on the
otherside going to the pid's.

Thinking RJ11 will be the best way to run power and data from the main box to
the pid's. Power, ground and the i2c lines.

Be using c++, qt, and qml for app on pi. Set it up as a kiosk so only this
program runs.

Probably need to drop an antenna wire out of the box if I need wifi.

Use json for storing recipe data.

The Anvil burners come with the shield and pot supports. And are made to bolt
down to a table so might be able to get away with a wood frame.

Can get 10 gallon Anvil kettles and a false bottom.

Looking like RIMS is the better choice, HERMS doesn't handle step mashing as
well.  Between the 4500Watt element and the burner should be able to get step
mashing to better then 2° per minute.

Need to set a log file tracking system temperatures and flow rates at 1 second
intervals.

Need brass pipe and values for plumbing the propane.

Need silicone tubing and some sort of interconnect system for plumbing the
rest.

Need removable insulation for the RIMS tube and any hot water tubing. Also need
insulation for the mash tun kettle.

Probably need some stereo phono jacks and plugs for the RTD's.

Might be nice to put the probes in the pots as well and use the display.

Should be able to set up 3 modes on the pump controllers
* Control based on flow rate
* Control based on flow rate for so much volume
* Control based on chillzilla outlet temperature

So should be able to set up the sparge to pump 7 gallons into the boil kettle
and set the pump from the HLT to the same rate and stop when the sparge pump
shuts off.

Also should be able to use the pump to go from the boil kettle through the
chillzilla to the fermenter but maintaining temp at the outlet below 75°.

Raspberry Pi and Atmel's ordered from Adafruit
Triac stuff ordered from Digikey

Need a i2c class with a mutex to ensure only one access at a time.

Need a class for each controller that will fire off a thread to monitor status
and params. Might even run commands as async's to keep gui fluid.

Still deciding if kettle temp's should be left as guages or monitored by
raspberry.
