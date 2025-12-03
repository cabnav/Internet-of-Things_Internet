# Bluetooth Controller Car Project

![FPT University](FPTU_logo.png)

## Overview
This project is an Arduino-based RC car controlled via Bluetooth, equipped with IR and ultrasonic sensors for obstacle detection and anti-fall mechanisms. The car can move forward, backward, turn left/right, and stop. WS2812B LEDs are used to indicate turn signals, reverse lights, and forward status. The project demonstrates autonomous and remote control capabilities with real-time feedback.

## Features
- **Bluetooth Control:** Remote control via smartphone using HC-05 module.
- **Obstacle Detection:** IR and ultrasonic sensors prevent collisions and detect edges.
- **Motor Control:** DC motors controlled via L298N driver with H-Bridge logic.
- **LED Indicators:** WS2812B LEDs for turn signals, reverse lights, and forward status.
- **Autonomous & Remote Control:** Can navigate obstacles automatically while responding to user commands.

## Technology Stack
- **Hardware:** Arduino Uno, HC-05 Bluetooth, L298N Motor Driver, IR Sensor HW-201, Ultrasonic Sensor HC-SRF05, WS2812B LEDs, Buzzer, DC Motors, Battery Pack.
- **Software:** Arduino IDE, C++ (Arduino sketches)
- **Libraries:** FastLED (for LED control)

## Circuit & System Diagrams
- Block Diagram: `Block diagram of the developed system.png`
- Circuit Diagram: `Circuit Diagram.png`
- Flowchart: `Flowchart.png`

## Setup Instructions
1. Connect the hardware components as per the circuit diagram.
2. Install the Arduino IDE and required libraries (FastLED).
3. Upload the `BluetoothControllerCar.ino` sketch to the Arduino Uno.
4. Pair your smartphone with the HC-05 Bluetooth module.
5. Use the Bluetooth app to send control commands to the car.

## Team Members
- Doan Ly Hong Minh – SE180733 (Leader, Code, Assembly)
- Ho Dang Quang – SE180734 (Block Diagram, Flowchart)
- Nguyen Van Bac – SE180739 (Report, Circuit Diagram)
- Phan Quoc Lam – SE182754 (Video Demo, Hardware Prep)
- Tran Van Quyet – SE181574 (Presentation, Documentation)

## License
This project is for educational purposes under FPT University IoT102T course.

