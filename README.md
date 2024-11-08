
# Smart Home Automation System

A dual-microcontroller-based smart home automation system implemented using two ATmega32 MCUs, communicating via USART. The system features password protection, a real-time clock display, and control of multiple room devices, including an automated temperature-controlled AC system.
![Overview](https://github.com/user-attachments/assets/eff8ad9f-1132-4087-9d36-6fcd80404894)

## Key Features

- **Password-Protected Access System**: Provides security with a timeout after failed attempts.
- **Real-Time Clock**: Displays current time with manual adjustment capability.
- **Multi-Menu Navigation System**: Allows control of various devices in the system.
- **Automated AC Control**: Temperature threshold-based activation of AC.
- **Individual Room Lighting Control**: Controls lighting in separate rooms.
- **TV Power Management**: Manages the TV power status.
- **USART-Based Inter-MCU Communication**: Enables data exchange between master and slave MCU.

## Hardware Components

### Master MCU Unit

- **Microcontroller**: ATmega32
- **Display**: 16x2 LCD
- **Input**: 4x4 Matrix Keypad
- **Status Indicators**: LEDs for "Admin Access" and "System Blocked"
- **Buzzer**: For security alerts
- **Buttons**: **Start** (to start the system) and **Reset_Clock** (to manually set the clock)

### Slave MCU Unit

- **Microcontroller**: ATmega32
- **Temperature Sensor**: For monitoring ambient temperature
- **Control LEDs**:
  - Three room lights
  - TV status
  - AC status

## System Operation

### Initial State

- Displays the real-time clock on the LCD.
- Allows clock adjustment through a reset button.

### Security System

- Permits three password attempts.
- Initiates a 20-second lockout with countdown display on the LCD after three failed attempts.
- Activates the buzzer during the lockout period.

### Menu System

- Three-tier menu structure for device control.
- Simple navigation using the numeric keypad.
- Quick access to all home automation features.

### AC Control

- User can set a temperature threshold.
- AC operates automatically based on ambient temperature.
- Continuous real-time temperature monitoring via the sensor.

## Communication Protocol

- **Protocol**: USART-based communication between MCUs.
- **Baud Rate**: 9600
- **Command Structure**: Single-byte commands used for device control and status updates.

## Future Improvements

- Integration of additional sensors (e.g., motion, humidity).
- Mobile app or web interface for remote access.
- Data logging for monitoring system activity.
