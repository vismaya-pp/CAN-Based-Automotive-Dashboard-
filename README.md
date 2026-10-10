# CAN-Based Automotive Dashboard System

## Overview
The CAN-Based Automotive Dashboard System is an embedded systems project developed using PIC18F4580 microcontrollers and Embedded C. It uses Controller Area Network (CAN) communication to exchange vehicle-related data between three Electronic Control Units (ECUs) and display essential dashboard information.

## Features
- Vehicle speed monitoring
- Gear position indication
- Engine RPM monitoring
- Temperature monitoring
- Left-turn and right-turn indicators
- Hazard indicator control
- CAN-based communication between three ECUs
- LCD-based dashboard display

## Hardware and Technologies
- **Microcontroller:** PIC18F4580
- **Programming Language:** Embedded C
- **Communication Protocol:** CAN
- **Peripherals:** ADC, Matrix Keypad, CLCD, Timers
- **Development Environment:** MPLAB X IDE and XC8 Compiler

## System Architecture
The project consists of three ECUs:

- **ECU 1:** Acquires vehicle parameters and transmits data over the CAN bus.
- **ECU 2:** Handles user inputs, including gear selection and turn/hazard indicator controls.
- **ECU 3:** Receives CAN messages and displays dashboard information on the character LCD.

## CAN Message Identifiers
| Parameter | CAN ID |
|---|---|
| Speed | `0x10` |
| Gear | `0x20` |
| RPM | `0x30` |
| Temperature | `0x40` |
| Indicators | `0x50` |

## Software and Tools
- MPLAB X IDE
- MPLAB XC8 Compiler
- Embedded C
- CAN Communication
- Microcontroller Peripheral Interfacing

## Project Structure
```text
CAN-Based-Automotive-Dashboard/
├── ECU1.X/
├── ECU2.X/
└── ECU3.X/
```

Each ECU contains its own source files, header files, and MPLAB X project configuration.

## Learning Outcomes
- Implementing CAN communication between multiple ECUs
- Interfacing microcontroller peripherals
- Developing modular embedded applications
- Handling sensor inputs and user controls
- Debugging and validating communication between ECUs

## Author
**Vismaya P P**

GitHub: [vismaya-pp](https://github.com/vismaya-pp)