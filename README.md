# 🤖 ROBOVANGUARD – WRO Future Engineers 2025

An intelligent autonomous vehicle engineered for the Future Engineers division of the World Robot Olympiad 2025. This sophisticated robotic system integrates advanced computer vision, inertial measurement technology, and proximity detection capabilities with high-precision directional control mechanisms to autonomously execute both Open Track and Obstacle Avoidance challenges.

---

## 📁 Repository Structure

- **t-photos/** → Team photographs (official competition images and candid moments)
- **v-photos/** → Six comprehensive vehicle perspectives (top, bottom, front, back, left, right views)
- **video/** → Performance demonstration recordings (30+ second Open Track & Obstacle navigation runs)
- **schemes/** → Electrical wiring diagrams, system block diagrams, and circuit schematics
- **src/** → Control algorithm source code and challenge execution routines
- **models/** → 3D printable mechanical components (STL file format)
- **other/** → Supplementary documentation and supporting materials

---

## 👥 Team Information

| Role          | Name                | Department   | Register Number |
| ------------- | ------------------- | ------------ | --------------- |
| Mentor        | Mr. S. Valai Ganesh | Mech (AP SG) | —               |
| Team Leader   | M. Manojkumar       | CSBS         | 953623244024    |
| Hardware Lead | V. Rakshit          | EEE          | 953623105044    |
| Mechanical    | P. Chandru          | Mech         | 953623114009    |

- **Team Name:** ROBOVANGUARD
- **Team ID:** 1129

---

## 🔧 Hardware Overview

### Central Controller – RoboGuard Unit (ESP32-based)

The main controller integrates computing, motor driving, and power management:

- **Dual-core ESP32 microcontroller** for real-time processing
- **Built-in 3200 mAh Li-ion rechargeable battery**
- **Status RGB LED indicators** (power, error, activity)
- **Start button** for initiating autonomous runs
- **Onboard motor driver (DRV8833)** to directly power DC and servo motors
- **Multiple I/O ports** for sensors (USB, GPIO, PWM)

### Motors and Actuation

#### Propulsion

- **BO DC Motor (dual-shaft)** – 300 RPM, 0.35 kg-cm torque
- Mounted at rear for forward and reverse movement

#### Steering

- **MG995 Servo Motor** – 10–12 kg-cm torque
- Provides Ackermann steering control with ±20° turning angles

### Sensors

#### Ultrasonic Sensors (6 units)

- **3 Front** (obstacle detection and wall following)
- **1 Rear** (reverse safety)
- **1 Left, 1 Right** (alignment within narrow lanes)

#### Color Sensor (TCS34725)

- Detects colored lines/zones (orange, blue)
- Built-in LED ensures reliable readings

### Structural Components

#### Chassis

- **4 mm acrylic sheet** (lightweight, durable, easy to machine)
- Centralized mounting for phone + controller

#### Mobile Holder

- Securely holds Android device for computer vision tasks via OTG cable

#### 3D-printed parts

- Sensor mounts, motor brackets, steering linkages, bearing supports

---

## 💻 Software Stack

### Development Environment

- **Arduino IDE:** Used for coding, compiling, and uploading firmware
- **Arduino C++:** Programming language for bot logic
- **RoboVision Android App:** Custom app for:
  - Object detection (sign boards, boxes, parking walls)
  - Communication with ESP32 via OTG

### Code Architecture

- Modular programming with separate functions for:
  - Mobility control
  - Obstacle detection
  - Line recognition
  - Sign box detection
  - Parking sequence

---

## 📏 Dimensions and Specifications

| Parameter                  | Value                       |
| -------------------------- | --------------------------- |
| **Length**                 | 280 mm                      |
| **Width**                  | 190 mm                      |
| **Height**                 | 250 mm                      |
| **Weight (without phone)** | 975 g                       |
| **Weight (with phone)**    | 1,120 g                     |
| **Wheel Diameter**         | 6.7 cm                      |
| **Ground Clearance**       | 0.8 cm                      |
| **Power Runtime**          | ~45 minutes per full charge |

---

## 🚗 Mobility Management

Mobility is a key factor in autonomous navigation:

- **Ackermann steering** ensures realistic, smooth turns
- **Forward/reverse** handled by BO motor with optimized torque-speed balance
- **Servo turning** calibrated to 20° left/right offset from neutral (100° center)
- **Dual-sensor counter-steering** keeps vehicle centered in lanes
- **Stability enhanced** by even weight distribution of phone + controller

---

## ⚙️ Motor Selection & Engineering Calculations

### Torque & Power

#### Torque = Force × Radius

- Wheel radius = 3.35 cm
- 0.35 kg-cm torque ≈ 0.1 N force at surface

#### Speed = Wheel RPM × Circumference

- Circumference ≈ 21 cm
- Max speed ≈ 1.05 m/s

#### Power = Torque × Angular Velocity

- 300 RPM ≈ 31.4 rad/s
- Power ≈ 1.1 W

### Selection Rationale

- **BO Motor:** Compact, lightweight, efficient at 3–12V
- **MG995 Servo:** High torque ensures reliable steering even under load

---

## 🏗️ Chassis & Mechanical Design

- **Base:** Laser-cut acrylic plate (280 × 190 mm)
- **Layout:** Rear BO motor, front servo, central phone mount
- **Supports:** 11 SLA 3D-printed parts used
- **Balance:** CG maintained at center to reduce tipping risk
- **Durability:** Bearings reduce wear, reinforced joints reduce vibrations

---

## 🔬 Engineering Principles

- **Newton's Second Law (F=ma):** Ensured sufficient torque for >1.1 kg load
- **Power Efficiency:** Motors run within rated voltage, reducing heat
- **Ground Clearance:** 0.8 cm for low CG, stable maneuvering
- **Ackermann Geometry:** Wheels align at common I-center during turns, minimizing slip

---

## 🔋 Power Management

- **Battery:** 3.7V 3200 mAh Li-ion
- **Charger:** TP4056 module
- **Converters:** MT3608 step-up regulators (3.3V logic, 5V motors/sensors)
- **Runtime:** ~40–50 minutes
- **Power Optimization:** Duty cycle control of motors, sensor sampling adjustment

---

## 🚧 Obstacle Management Strategy

### Straight Path

- Left US < 30 cm → Turn right
- Right US < 30 cm → Turn left
- Both clear → Continue straight

### Corner Section

- **Orange Line** → Clockwise turn
- **Blue Line** → Counterclockwise turn

### Sign Box Detection

- **Red Box** → Right turn
- **Green Box** → Left turn
- Detection via RoboVision app → values transmitted to ESP32

### Parking Lot

- After 3 laps, app identifies parking walls
- Controller executes parking sequence

---

## 🔄 Firmware Flow

1. **Power ON** → Start button pressed
2. **Main control loop** activated
3. **Sequence executed:**
   - Straight path navigation
   - Corner detection and turning
   - Obstacle/box avoidance
   - Final lap parking routine

This ensures smooth transitions across all phases of the Future Engineers challenge.

---

## 🛠️ Tools & Assembly

### Tools Used

- Screwdriver set (M3/M4)
- Needle-nose pliers
- Nut drivers

### Assembly Steps

1. Fix controller onto chassis
2. Attach front sensor mount
3. Secure phone holder at center
4. Mount motors and wheels
5. Wire sensors and motors to controller

### 3D Printed Parts

- Ultrasonic sensor holders (front, side, rear)
- Motor holder
- Start button holder
- Pivot bush + linkages

---

## 🎯 Conclusion

The **ROBOVANGUARD bot** combines **ESP32-based control**, **Ackermann steering**, and a **robust sensor suite** to navigate the WRO Future Engineer track. It is:

- **Lightweight yet durable**
- **Power efficient** with 45-min runtime
- **Intelligent** through obstacle detection and app-based vision

With its interdisciplinary design (CSBS + EEE + MECH collaboration), the robot is a practical demonstration of **AI-driven mobility**, **engineering design principles**, and **teamwork across domains**.

---

## 📚 Additional Resources

For detailed technical specifications, circuit diagrams, and source code, please explore the respective directories in this repository. Each folder contains comprehensive documentation and resources for understanding and replicating the ROBOVANGUARD system.
