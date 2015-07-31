# ps3EyeSyphon_2
Updated App for using multiple PS3Eye cameras with Syphon and OSC on OSX 10.9 and 10.10

For a precompiled binary visit the releases section of this repo here https://github.com/fred-dev/ps3EyeSyphon_2/releases/tag/0.0.1.beta.1

This version requires 

openframeworks 0.9.0 
https://github.com/openframeworks/openFrameworks

ofxPS3EyeGrabber 
https://github.com/bakercp/ofxPS3EyeGrabber/branches

ofxSyhpon
https://github.com/astellato/ofxSyphon

XML Settings (inside bin/data) change the values as needed

"\<CAMWIDTH\>320\</CAMWIDTH\>"
"\<CAMHEIGHT\>240\</CAMHEIGHT\>"
"\<FRAMERATE\>20\</FRAMERATE\>
"\<RECIEVEPORT\>1234\</RECIEVEPORT\>"
"\<SENDPORT\>1235\</SENDPORT\>"
"\<SENDIP\>127.0.0.1\</SENDIP\>"


OSC Controls input
set port with XML

Settings for the whole app
minimise anything -minimises app to tiny window
saveSettings anything
recallSaved anything

Settings dependant on camera number - replace Camera Number in address with the camera ID


"/Camera Number/gain int 0-63"

"/Camera Number/draw int 0 -255"

"/Camera Number/exposure int 0 -255"

"/Camera Number/sharpness" int 0 -255"

"/Camera Number/brightness"int 0 -255"

"/Camera Number/contrast"int 0 -255"

"/Camera Number/hue"int 0 -255"

"/Camera Number/blueBalance"int 0 -255"

"/Camera Number/redBalance" int 0 -255"

"/Camera Number/autoGain"int 0 or 1"

"/Camera Number/autoWhiteBalance" int 0 or 1"

"/Camera Number/flip" 2 ints vert 0 or 1, horizontal 0 or 1"


Some controls are not available when with autoGain or autoBalance are on

OSC controls output
Set IP address and port with XML settings

Key Commands

‘g’ show or hide GUI controls

‘m’ Toggle tiny mode

’s’ Save settings

‘r’ recall saved settings

	

Updates- 

	•	Allows for frame size to be set

	•	Sends all settings via OSC

	•	New Tiny mode to save screen real estate

	•	Now app is 64bit

	•	Better frame rates (single camera at 320*240 will run at 200 fps depending on your computer)**

	•	App requires OS X 10.10 


** Your graphics card may not be able to deliver 200 fps through syphon and depending on the syphon implementation you use this may be too fast. to save CPU cycles and video memory set a lower framerate in the settings file.
