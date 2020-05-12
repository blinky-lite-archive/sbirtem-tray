# Vad Kul Thermal Camera
The Vad Kul Camera is an open-source and inexpensive thermal camera based on a Raspberry Pi equipped with a camera module and an AMG8833 thermopile array.
## Parts
- [Raspberry Pi 3A+ (or equivalent)](https://www.electrokit.com/en/product/raspberry-pi-3-model-a/)
- [Case for Raspberry Pi](https://www.electrokit.com/en/product/enclosure-for-raspberry-pi-mod-a-transparent-smoke/)
- [Raspberry Pi Camera Module](https://www.electrokit.com/en/product/camera-module-for-raspberry-pi-v-2/)
- [Sparkfun AMG8833 Breakout board](https://www.electrokit.com/en/product/grid-eye-amg8833-monterad-pa-kort/)  

The part cost before tax is about 1100 SEK (or about 110 USD)
## Raspberry Pi setup with pre-loaded disk image.
- Connect the AMG8833 GND, 3.3V, SDA, and SCL pins to the Raspberry Pi GPIO pins 9, 1, 3, 5 respectively (with power off of course)
- Connect the Raspberry Pi Camera (with power off of course)
- [Download](https://www.dropbox.com/s/j3wf9a0tfl4xb0a/vad-kul-tray.zip?dl=0) and burn Raspbian image with Vad Kul already installed.
- When powered up, the Raspberry Pi will run Vad Kul automatically and the Raspberry Pi will act as a wireless hotspot. You can see the SSID of the hotspot is *vad-kul-01* and the password is *blinky-lite*
- Once connected to the Raspberry Pi hotspot navigate your browser to http://192.168.4.1 to see the application

## Manual Raspberry Pi Setup
- Connect the AMG8833 GND, 3.3V, SDA, and SCL pins to the Raspberry Pi GPIO pins 9, 1, 3, 5 respectively (with power off of course)
- Connect the Raspberry Pi Camera (with power off of course)
- Download and burn Raspbian image on SD card.
 - I use stretch because it is easier to install a wireless hotspot on the Raspberry Pi [2019-04-08-raspbian-stretch-lite.zip (latest, lite)](http://downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-2019-04-09/2019-04-08-raspbian-stretch-lite.zip)
- If desired, make the Raspberry Pi a wireless hotspot following this [link](https://thepi.io/how-to-use-your-raspberry-pi-as-a-wireless-access-point/). Note this will not work for Buster
- Enable the camera and I2C interfaces using `sudo raspi-config`
- Install Node.js on the Raspberry pi by following this [link](https://www.instructables.com/id/Install-Nodejs-and-Npm-on-Raspberry-Pi/)
- Install pm2 globally if desired for running in [background](https://nodered.org/docs/faq/starting-node-red-on-boot) and at startup by `sudo npm install -g pm2`
- In the /home/pi directory of the Raspberry Pi clone this repository
- Enter the project directory and `npm install` the node imports
- create a file .env in the project directory and add the following lines  
`PROJECT=blinky-lite`  
`JWTKEYSECRET=`*some-random-string-you-pick*  
`SETTINGSPASSWORD=`*your-choice*  
`NODEREDCONFIGSECRET=`*another-choice*
- To run the code from the project directory enter `./run-blinky-lite.sh $(pwd)`
- OR to run the code in background enter from the project directory `./pm2.sh $(pwd)`
 - The Raspberry Pi now becomes a web server and you can see the application by pointing a web browser at the raspberry Pi at port 1883  
