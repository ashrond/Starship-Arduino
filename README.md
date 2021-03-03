# Starship-Arduino
Arduino lighting control program for starship models intended to be changed via button or reed switch. This is something thrown together to animate starship et.al models which allows for multiple states of lighting EG. Docked, Sublight, FTL states. It could also be used with other model types, RC craft/Drones ect. It takes insperation from an included older program which was found on a now defunct website which emulated the 1979 movie enterprise lighting and was unsuitable for use/modification

The program was developed with an arduino metro mini/Uno but should be ok with other arduino types which have enough PWM connections.

Bugs: the program works overall but does not change states correctly EG. the result of changing a state leaves lights trying to be in 2 states at the same time (flickering between the 2 different light levels) I have not been able to determine why as of yet.

I am releasing this as publicly so that others may enjoy and make use of it and in the hopes that someone else might solve the issue when changing states and to share the fix.
