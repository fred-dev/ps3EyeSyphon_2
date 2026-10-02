# ps3EyeSyphon_2

macOS app that runs several PS3 Eye cameras at full frame rate and publishes each one as a Syphon server. Per-camera exposure, gain, white balance and flip are set from a GUI or over OSC, and saved to `bin/data/cameraSettings.xml`. The OSC ports are set in the app and saved to `bin/data/settings.xml`.

Successor to an earlier multi-camera PS3 Eye Syphon tool (2012-2018), updated in 2023.

## Build

- Addons: `ofxGui`, `ofxOsc`, `ofxPS3EyeGrabber`, `ofxSyphon`, `ofxXmlSettings`
- Generate the project with projectGenerator (macOS only, because of Syphon).
