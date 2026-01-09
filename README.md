<p align="center">
  <img src="assets/logo.png" width="600" valign="middle" alt="TicTacToeBot Logo" />
</p>



<p align="center">
  <img src="https://img.shields.io/badge/platform-ESP32%20%7C%20Arduino-blue" alt="Platform">
  <img src="https://img.shields.io/badge/2023_McMaster_Eng_Comp-2nd_Place-850633" alt="Competition">
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License: MIT">
</p>

**A high-speed, wireless robotics system designed for competitive precision and speed.**



TicTacToeBot is a remote-operated vehicle and control system built for the **2023 McMaster Engineering Competition (Senior Design Challenge)**. The project features a custom-built robot and a low-latency wireless controller designed to navigate obstacle courses and execute precise movements to win an advanced Tic-Tac-Toe relay.

> **🏆 Achievement:** Awarded **Fastest Time-To-Complete** and placed **2nd Overall** ($200 Prize) in a field of elite engineering teams.

---

## ✨ Key Features

* **📡 Low-Latency Wireless Control:** Utilizes dual ESP32 modules for high-speed Wi-Fi communication, ensuring near-instant response times between the controller and the bot.
* **🔄 Tank-Turn Maneuverability:** Features a dedicated **SPIN button** that reverses one motor while driving the other, enabling rapid 360-degree rotation in place.
* **🏗️ Precision Lever System:** Includes a 9-gram servo-controlled lever designed for long reach and end-point rotation to interact with game elements.
* **⚡ Speed-Optimized Design:** Purposefully minimalist, being the smallest and lightest bot in the competition to maximize acceleration and nimbly traverse the course.
* **🛠️ Fault-Tolerant Firmware:** Modular C++ code architecture designed for high-frequency polling and reduced signal interference.

---

## 📋 Bill of Materials (BOM)

The hardware was carefully selected to maximize performance within strict competition constraints:

| Category | Components |
| :--- | :--- |
| **Electronics** | 2x ESP32 Modules, 1x L298N Motor Driver, 2x 9V Batteries |
| **Actuators** | 2x DC Motors, 1x 9g Servo (Lever) |
| **Chassis** | 1x Foam Poster Board, 1x Ball Bearing Wheel, 2x Motor Wheels |
| **Hardware** | 7x Tactile Buttons, 5x Wooden Skewers, 6x Rubber Bands, 1x Pipe Cleaner |

---

## 🛠️ System Architecture

1.  **Low-Latency Polling:** The controller polls 7 hardware buttons at high frequency to capture directional and utility inputs.
2.  **Wireless Handshake:** Facilitates real-time communication via ESP32 Wi-Fi protocols to minimize physical tethering.
3.  **3-Point Contact:** The mechanical base utilizes two drive wheels and a single ball-bearing wheel for efficient rotation and stability.
4.  **Modular Codebase:** The software separates motor control, wireless communication, and lever actuation for ease of maintenance and debugging.

---

## 👥 The Team: *Three and a Half Mechs*

* **Aidan Goodyer** – Software Engineering
* **Jasan Rubes** – Mechanical Engineering
* **Grayson Wood** – Mechanical Engineering
* **Jared Ducharme** – Mechanical Engineering

---

## ⚖️ License

Distributed under the MIT License. See [LICENSE](./LICENSE) for more information.
