# ESP32-BLE-Wireless-IO-Control


This project lets two ESP32 boards talk to each other without wires using Bluetooth. One board (the **transmitter**) takes information in, and the other board (the **receiver**) controls things based on that information.

## What You Need

* Two ESP32 development boards.
* Arduino IDE (a free program for writing and uploading code).
* USB cables to connect the ESP32 boards to your computer.

## Hardware Components

### Receiver

* 1 x 7805 Voltage Regulator
* 10 x 12V Relays
* 10 x BD135 Transistors
* 10 x 1N4007 Diodes
* 10 x 10kΩ Resistors
* 2 x 100µF 16V Electrolytic Capacitors
* 2 x Ceramic Capacitors (marked "104")
* Receiver PCB (design files included)

**Important Wiring Note for Receiver PCB:**

* On the receiver PCB, you need to manually connect **ESP32 pin D19** to the corresponding resistor pad. These are connected with a net named **C1** in the PCB file. Use a wire to solder these two points together.
* Similarly, manually connect **ESP32 pin D21** to its corresponding resistor pad. These are connected with a net named **C3** in the PCB file. Use a wire to solder these two points together.

### Sender

* 10 x 1kΩ Resistors
* 9 x Push Button DIP Switches
* 1 x SPST Slide Switch
* 1 x 3xAA Battery Holder (for 3 x 1.5V AA batteries)
* Sender PCB (design files included)

## How to Set Up

1.  **Install Arduino IDE:**
    * Go to the Arduino website: [https://www.arduino.cc/software](https://www.arduino.cc/software)
    * Download and install the Arduino IDE for your computer. Follow the instructions on the website.

2.  **Install ESP32 Support in Arduino IDE:**
    * Open the Arduino IDE.
    * Click on `File` in the top menu, then click on `Preferences`.
    * Find the box labeled "Additional Boards Manager URLs".
    * Copy and paste this link into the box: `https://dl.espressif.com/dl/esp32_arduino_index.json`
    * Click "OK".
    * Now, go to `Tools` in the top menu, then `Board`, and then `Boards Manager...`.
    * In the search box, type "esp32".
    * Find "esp32 by Espressif Systems" and click "Install". Wait for it to finish.

3.  **Get the Code:**
    * You can download the code files directly from this project on GitHub.
    * The code for the **transmitter** ESP32 (the one with `#include "BLEDevice.h"` at the top) is located in the **`sender`** folder.
    * The code for the **receiver** ESP32 (the one with `#include <BLEDevice.h>` and `#include <BLEUtils.h>`) is located in the **`receiver`** folder.
    * Download these two `.ino` files to your computer.

4.  **Upload Code to the Transmitter ESP32:**
    * Open the transmitter code file (from the `sender` folder) in the Arduino IDE.
    * Connect one of your ESP32 boards to your computer with a USB cable.
    * In the Arduino IDE, go to `Tools` -> `Board` and choose your ESP32 board (it might be called something like "ESP32 Dev Module").
    * Go to `Tools` -> `Port` and select the USB port that your ESP32 is connected to.
    * Click the "Upload" button (it looks like an arrow pointing to the right). Wait until the code says "Done uploading."

5.  **Upload Code to the Receiver ESP32:**
    * Disconnect the first ESP32.
    * Connect the other ESP32 board to your computer with a USB cable.
    * Open the receiver code file (from the `receiver` folder) in the Arduino IDE.
    * Make sure the correct board and port are selected (you might need to check `Tools` -> `Port` again).
    * Click the "Upload" button. Wait until the code says "Done uploading."

## How to Use

1.  After uploading the code to both ESP32 boards, disconnect them from your computer.
2.  Assemble the hardware components on the sender and receiver PCBs according to the design files.
3.  **Receiver:** Ensure you have made the manual wire connections between ESP32 pin D19 and net C1, and between ESP32 pin D21 and net C3.
4.  Power both ESP32 boards. The sender will likely be powered by the 3 AA batteries. Provide a suitable power source (likely 12V based on the relays) for the receiver, connected through the 7805 regulator to power the ESP32.
5.  The **transmitter** board will read the state of its input pins (connected to the DIP switches and slide switch). When the state of an input changes, the transmitter will send a message wirelessly to the **receiver** board.
6.  The **receiver** board will receive this message and then control the state of its output pins (connected to the relays).
7.  For example, if you change the state of a DIP switch on the transmitter, a corresponding relay on the receiver will likely change its state (turn on or off, depending on your wiring and the code logic).

## What the Code Does

* **Transmitter Code:** This code (in the `sender` folder) makes the ESP32 act like a sender. It looks at the input pins and uses Bluetooth to tell the receiver what is happening.
* **Receiver Code:** This code (in the `receiver` folder) makes the other ESP32 act like a listener and controller. It waits for messages from the transmitter and then changes the state of its output pins (connected to the relays) based on those messages.

## License

This project is licensed under the **Apache License 2.0**. See the `LICENSE` file for more information.

## Contact

You can contact me at [jafaryaz220@gmail.com].
