# esp32-diorama
### LEDs respond to touch with ESP32
The ESP32 microcontroller supports touch-sensing on up to 10 of its General-Purpose Input/Output (GPIO) pins. 

This means we can use an ESP32 to drive a simple device that switches a current when a sensor is touched. A sensor can be almost anything, even a bare wire. 

This project demonstrates sensing touch with inexpensive earring backs of the kind popular with jewelry craft hobbyists. We build a device that turns an LED on or off when someone touches one of these low-cost sensors.

A device like this can transform a static display such as a poster into an interactive display. The device can be powered with a battery or by a USB connection to a computer, as the user may choose.

No coding is required to use the device. The only coding involved is to upload the firmware, from this repository, onto the device. 

### The hardware
Components of the prototype described here include:
* HiLetgo NodeMCU-32S development board for ESP32
* a breadboard
* a battery power adapter
* jumper wires
* LEDs
* earring backs and post retainers

### Assembly
The HiLetgo NodeMCU development board is among the narrowest form factors we evaluated. It provides 38 pinouts on male headers -- 19 on each side -- correctly spaced to mount securely on a breadboard. Locate a position for the device that will leave a row of pinholes open on the breadboard adjacent to each side of the NodeMCU.

For example, our breadboard had 63 rows of pins, each row having a group of 5 columns of pinholes (numbered a through e) on the left side and another group of 5 columns (numbered f through j) on the right side. The two groups of columns are separated and isolated from each other. We planned our project to seat the NodeMCU board's header pins into columns b and i of rows 45 through 63. In other words, we centered it on the bottom rows of the breadboard.

This arrangement leaves columns a, c, d and e available for connection to header pins on the left-hand side of the NodeMCU board. Likewise, columns f, g, h and j are accessible for connectio to header pins on the right-hand side.

The HiLetgo NodeMCU board does not exhibit pin labels on the top side. We used the following table to map the header pins to the rows and columns on the breadboard. Left and right are defined viewing the breadboard from above, with row 1 at the top and the NodeMCU at the bottom, closest to the observer. A letter "L" after a row number denotes the left-hand side of the device; an "R" denotes the right-hand side.

"(T)" in the Function column indicates GPIO pins that we used for touch sensing.  "(S)" in the Function column indicates GPIO pins that we used to switch current on and off, in this case to light up our LEDs. "(TX)" and "(RX)" refer to the transmit and receive pins, respectively, reserved for future use in serial communications.
It also meant that we could make use of columns c, d and e on the left side and columns f, g and h on the right.

| Function   | Pin Left | Pin Right | Function   |
| ---------- |:--------:|:---------:| ---------- |
| VIN 3.3v   | 45L      | 45R       | GND        |
| EN (reset) | 46L      | 46R       | GPIO23 (S) |
| GPIO36     | 47L      | 47R       | GPIO22 (S) |
| GPIO39     | 48L      | 48R       | GPIO1 (TX) |
| GPIO34     | 49L      | 49R       | GPIO3 (RX) |
| GPIO35     | 50L      | 50R       | GPIO21 (S) |
| GPIO32 (T) | 51L      | 51R       | GND        |
| GPIO33 (T) | 52L      | 52R       | GPIO19 (S) |
| GPIO25     | 53L      | 53R       | GPIO18 (S) |
| GPIO26     | 54L      | 54R       | GPIO5 (S)  |
| GPIO27 (T) | 55L      | 55R       | GPIO17 (S) |
| GPIO14 (T) | 56L      | 56R       | GPIO16 (S) |
| GPIO12 (T) | 57L      | 57R       | GPIO4 (T)  |
| GND        | 58L      | 58R       | GPIO0      |
| GPIO13 (T) | 59L      | 59R       | GPIO2      |
| GPIO9      | 60L      | 60R       | GPIO15 (T) |
| GPIO10     | 61L      | 61R       | GPIO8      |
| GPIO11     | 62L      | 62R       | GPIO7      |
| VIN 5v     | 63L      | 63R       | GPIO6      |

This table guided the planning of our touch sensors and LEDs. We organized them into pairs: 1 touch sensor and 1 LED making a pair. We numbered the pairs 0 through 7 for ease of coding, as explained in the next section.

We want a simple function. Touching the sensor of pair 0 would switch the current on or off to the LED of pair 0. Do the same for the other pairs. The following table lists the way we organized the pairs. This ordering made it easier (in my mind, at least) to lay out the wiring from the NodeMCU to the touch sensors and LEDs

| Pair # | Touch Pin    | LED Pin      |
| ------ | ------------ | ------------ |
| 0      | GPIO4 = 57R  | GPIO16 = 56R |
| 1      | GPIO15 = 60R | GPIO17 = 55R |
| 2      | GPIO13 = 59L | GPIO5 =  54R |
| 3      | GPIO12 = 57L | GPIO18 = 53R |
| 4      | GPIO14 = 56L | GPIO19 = 52R |
| 5      | GPIO27 = 55L | GPIO21 = 50R |
| 6      | GPIO33 = 52L | GPIO22 = 47R |
| 7      | GPIO32 = 51L | GPIO23 = 46R |

220-ohm resistors were used in the LED circuits. I am going to assume that the reader either already knows how to wire an LED using a microcontroller and a breadboard. Or, the reader is capable and willing to pursue self-directed learning from any of the myriad tutorials that can be found by searching the web.

We leave it to the reader also to determine how to run the wiring if the reader decides to build their own version of the prototype.

### Code
The HiLetgo NodeMCU-ES32 development board can be programmed using a number of different tools. The code available here was written with the Arduino IDE after installing the ESP32 add-on package. Again, instructions for how to do this can be found by searching the web. For example, try searching for "Arduino install ESP32". 

Choose a tutorial that also demonstrates selecting the serial port and specific model of board. For example, using our HiLetgo NodeMCU-32S on a Linux box, we selected the /dev/ttyusb0 port and the NodeMCU-32S board from lists available in the Arduino IDE.

Copy the code from this repo and paste it into the Arduino IDE. Ensure that the device is connected to the computer with a USB cable and the Arduino IDE has the serial port and the board model selected. Click the Upload icon (a right-pointing arrow) or choose "Upload" from the Sketch menu.

When all goes well, the Arduino software performs a three-step procedure when the user tells it to upload code to a device:
* Step 1: compile the code
* Step 2: connect to the device
* Step 3: move the code onto the device

This sequence is familiar and automatic for users accustomed to programming many types of boards with the Arduino software. However, the ESP32 throws an extra wrinkle into the procedure.

The HiLetgo NodeMCU-32S requires the user to press a button on the device at the point of Step 2, when the Arduino software begins trying to connect. The button is labeled "IO0". The text is so tiny that it almost looks like a number, "100". The button is near the lower-right corner of the device.  Hold the button down until the Arduino software indicates that it has completed the connection and begun the upload process. The upload will continue even if you release the button after the connection is established.
