# B20_Group22

### Smart Navigating Robot

The Smart Robot is an autonomous robotic vehicle designed to be controlled and monitored through a web-based interface. Powered by a NodeMCU ESP32 (38-pin) microcontroller, the robot integrates various components such as motor controllers, IR speed sensors, and a user-friendly web page for seamless interaction. This project aims to provide a flexible and efficient robotic platform that can be remotely controlled and programmed to follow user-defined paths with minimal human intervention.

The robot is equipped with real-time motion feedback using IR speed sensors, enabling it to make precise adjustments during movement. Users can interact with the robot through a web page, where they can draw custom paths on a grid, start or stop the vehicle, and modify movement parameters such as speed and direction. The web interface communicates with the ESP32 microcontroller via a server API, ensuring real-time control and monitoring.

To ensure stable power distribution, a buck converter regulates voltage levels, preventing potential fluctuations that may affect motor performance. The robot's modular design allows for easy integration of additional sensors or modules, making it highly adaptable for various applications.

**Components used :**

- NodeMCU ESP32 Microcontroller
- L298N Motor Driver
- 11v to 5v Buck Converter
- IR Speed Sensors
- DC Gear Motors
- 11.1V Lipo Battery

**Circuit diagram:** 

<img src="https://github.com/user-attachments/assets/d57ebcfa-006e-4a1f-91a5-d8c67e872884" width="800">


