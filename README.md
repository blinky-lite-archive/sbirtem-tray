# Vad Kul Thermal Camera
The Vad Kul Camera is an open-source and inexpensive thermal camera based on a Raspberry Pi equipped with a camera module and an AMG8833 thermalpile array.
## Parts
- [Raspberry Pi 3A+ (or equivalent)](https://www.electrokit.com/en/product/raspberry-pi-3-model-a/)
- [Case for Raspberry Pi](https://www.electrokit.com/en/product/enclosure-for-raspberry-pi-mod-a-transparent-smoke/)
- [Raspberry Pi Camera Module](https://www.electrokit.com/en/product/camera-module-for-raspberry-pi-v-2/)
- [Sparkfun AMG8833 Breakout board](https://www.electrokit.com/en/product/grid-eye-amg8833-monterad-pa-kort/)  

The part cost is about 1370 SEK (or about 140 USD)
## Raspberry Pi Setup
- Connect the AMG8833 GND, 3.3V, SDA, and SCL pins to the Raspberry Pi GPIO pins 9, 1, 3, 5 respectively (with power off of course)
- Connect the Raspberry Pi Camera (with power off of course)
- Download and burn Raspbian image on SD card.
 - I use stretch because it is easier to install a wireless hotspot on the Raspberry Pi [2019-04-08-raspbian-stretch-lite.zip (latest, lite)](http://downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-2019-04-09/2019-04-08-raspbian-stretch-lite.zip)
- If desired, make the Raspberry Pi a wireless hotspot following this [link](https://thepi.io/how-to-use-your-raspberry-pi-as-a-wireless-access-point/). Note this will not work for Buster
- Enable the camera and I2C interfaces using `sudo raspi-config`
- Install Node.js on the Raspberry pi by following this [link](https://www.instructables.com/id/Install-Nodejs-and-Npm-on-Raspberry-Pi/)
- In the /home/pi directory of the Raspberry Pi clone this repository
- Enter the project directory and `npm install` the node imports
- create a file .env in the project directory and add the following lines  
`PROJECT=blinky-lite`  
`MQTTCLIENTID=vad-Kul-tray-01`  
`MQTTSERVERIP=none`  
`MQTTUSERNAME=none`  
`MQTTPASSWORD=none`  
`JWTKEYSECRET=`*some-random-string-you-pick*  
`SETTINGSPASSWORD=`*your-choice*  
`NODEREDCONFIGSECRET=`*another-choice*  
