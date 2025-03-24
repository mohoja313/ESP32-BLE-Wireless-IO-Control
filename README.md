# ESP32-BLE-Wireless-IO-Control


This project lets two ESP32 boards talk to each other without wires using Bluetooth. One board (the **transmitter**) takes information in, and the other board (the **receiver**) controls things based on that information.

## What You Need

* Two ESP32 development boards.
* Arduino IDE (a free program for writing and uploading code).
* USB cables to connect the ESP32 boards to your computer.

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

1.  After uploading the code to both ESP32 boards, you can disconnect them from your computer.
2.  Power both ESP32 boards using a power supply if needed.
3.  The **transmitter** board will read the state of its input pins (labeled `k1` to `k10` in the code). When the state of an input pin changes, the transmitter will send a message wirelessly to the **receiver** board.
4.  The **receiver** board will receive this message and then change the state of its output pins (labeled `R1` to `R10` in the code).
5.  For example, if the input at `k1` on the transmitter changes, the output at `R1` on the receiver will likely change its state (turn on or off, depending on how you connected things). The code tells the boards exactly how the inputs and outputs are linked.

## What the Code Does

* **Transmitter Code:** This code (in the `sender` folder) makes the ESP32 act like a sender. It looks at the input pins and uses Bluetooth to tell the receiver what is happening.
* **Receiver Code:** This code (in the `receiver` folder) makes the other ESP32 act like a listener and controller. It waits for messages from the transmitter and then changes the state of its output pins based on those messages.

## License

This project is licensed under the **Apache License 2.0**. See the `LICENSE` file for more information.

## Contact

You can contact me at [jafaryaz220@gmail.com].
