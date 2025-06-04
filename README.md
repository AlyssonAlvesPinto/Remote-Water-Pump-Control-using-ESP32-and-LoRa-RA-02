# Remote-Water-Pump-Control-using-ESP32-and-LoRa-RA-02
This project enables remote control of a water pump based on two water level sensors (minimum and maximum), using LoRa communication between two ESP32 boards. 

![image alt](https://github.com/AlyssonAlvesPinto/Remote-Water-Pump-Control-using-ESP32-and-LoRa-RA-02/blob/main/Esp32LoraRA-02.png?raw=true)


🔧 Components 
2 × ESP32
2 × LoRa RA-02 modules + adapter (with 3.3V regulator)
2 × Water level sensors (float or resistive)
1 × 5V Relay Module
Power supply
Jumper wires and breadboard 



🧠 Operation 
The Remote ESP32 (sender) monitors water levels at the reservoir.
It sends a signal via LoRa when either minimum or maximum level is reached.
The Base ESP32 (receiver) receives the signal and activates/deactivates the water pump accordingly. 


📡 LoRa CommunicationLevel Detected Signal SentMinimum LOWMaximum HIGH 



🔌 Schematic 
Check the wiring diagram in docs/schematic.png. 

🛠️ Setup Instructions 
Upload sender.ino to the reservoir ESP32.
Upload receiver.ino to the pump controller ESP32.
Power up the circuits.
Use the serial monitor for debugging. 


📜 License 
MIT License
