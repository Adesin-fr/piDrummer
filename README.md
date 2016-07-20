# urDrummer
urDrummer is a DIY drum trigger device. it uses an Arduino and some basic components to get the signal from your pads (AKA triggers) and send them to an Orange PI PC.
The Orange PI PC is used to play sounds according to the triggers you hit. 
Thanks to CPU power of a such board computer, it is possible to play the best sound quality !
The oPI PC is also driving an ILI9341 TFT screen (320x240 pixels, can be found as cheap as 5$ on ebay ) and displays an interface that allows you to set up your different drum kits, the volume, sound effects (reverb, equalizer, etc...), and map each trigger to an instrument.

The goal is also to build an embedded linux, with the smallest possible kernel, allowing for very small boot time !
