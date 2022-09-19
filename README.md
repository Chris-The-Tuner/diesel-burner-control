# diesel-burner-control
Small arduino script to control a Diesel burner (or any simple oil burner).

I had a "small" Webasto Diesel Burner out of the DW Series laying around but the controls where compledly missing.
Being me i wrote this little script to control a few Relays and get the status of the Flame sensor (conveniently it is just a photoresistor that pulls against ground if flame is there) and a few buttons/switches to control it.

How it works:
It first boots into idle state and waits for the switch to be turned on (Call 4 Heat).
A Thermostat would be a good way to control this.

If there is a Call 4 Heat it starts a sequence:
 - Start the Blower (the Fuel pump runs with the blower)
 - Wait to get fresh combustion air in and get everything that may be dangerous out of the burning system
 - Open the fuel solenoid
 - Wait 2 seconds for the jet to start vaporizing the fuel
 - Turn on the spark ignition
 - Wait 3 seconds
 - Turn off the spark ignition
 
After that, the script waits 5 seconds to get the flame going good before going into run operation
While the burner is running the flame sensor gets checked every half second.
This is mission critical, if the flame stops for any reason the fuel supply gets shut down instantly and the blower runs for 1 minute to purge the wholy system of any fuel that may be left.
Then the system locks itself out until you press the fail-reset button which turns off the locked state and the system would resume normal operation.

I programmed this in spare time out of curiosity.

Take this with a grain of salt, i don't guarantee that this script is performing perfectly !
If you screw up and burn down your shed/house, don't call me responsible, i use this in my Garden shed and it works just fine, but your application may be different.

Any suggestions/ideas are welcome tho, i may implement WiFi (using ESP8266) to send/recive messages via MQTT for remote control in the future but for now this works for me :)
