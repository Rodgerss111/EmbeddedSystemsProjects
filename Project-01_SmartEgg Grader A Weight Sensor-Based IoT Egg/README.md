# 🥚 SmartEgg Grader
### Arduino & ESP32-Based IoT Egg Grading System with Cloud Monitoring and Voice Assistance

> **A low-cost embedded system that automates egg grading using weight sensing, servo-based sorting, cloud connectivity, and real-time voice guidance for small-scale poultry farms.**

---

## 📌 Overview

Manual egg grading is labor-intensive and susceptible to inconsistent classification caused by human error. While commercial grading machines offer high accuracy, their cost makes them inaccessible to many small poultry farms.

SmartEgg Grader addresses this problem by combining **embedded systems, automation, and IoT** into an affordable prototype capable of:

- Automatically retrieving eggs one at a time
- Measuring egg weight using a load cell
- Classifying eggs into Grade A or Grade B
- Physically sorting eggs using servo motors
- Displaying real-time information on LCD screens
- Uploading grading statistics to ThingSpeak
- Providing spoken user guidance using a DFPlayer Mini

The project demonstrates how low-cost embedded hardware can replicate many features found in industrial egg grading systems.

---

# 🎯 Features

✅ Automatic Egg Feeding

- Retrieves eggs one-by-one from the roller mechanism.

✅ Weight-Based Classification

- Uses an HX711 load cell amplifier with a 1 kg load cell.

✅ Automatic Sorting

- Servo motors route eggs into their corresponding grade.

✅ Dual Operating Modes

- Home Mode
- Automatic Grading Mode

✅ Rotary Encoder Interface

- Simple user interaction without buttons.

✅ Cloud Monitoring

- Uploads grading statistics to ThingSpeak using ESP32 WiFi.

✅ Voice Feedback

- Audio prompts announce grading status and cloud updates.

✅ Real-Time LCD Dashboard

Displays:

- Current egg weight
- Total eggs sorted
- Grade A count
- Grade B count
- Last sorting duration

---

# 🏗 Hardware

| Component | Purpose |
|------------|----------|
| Arduino Uno R3 | Main Controller |
| ESP32 | WiFi Communication |
| HX711 | Load Cell Amplifier |
| 1kg Load Cell | Egg Weight Measurement |
| Servo Motor #1 | Egg Feeding Mechanism |
| Servo Motor #2 | Egg Sorting Platform |
| DFPlayer Mini | Voice Prompt Module |
| Rotary Encoder | Mode Selection |
| Dual 16x2 I2C LCDs | User Interface |
| 4×18650 Batteries | Portable Power Supply |

---

# ⚙ System Architecture

```
Egg Roller
     │
     ▼
Servo 1
     │
     ▼
Load Cell Platform
     │
Weight Measurement
     │
     ▼
Arduino Uno
     │
 ┌────┴───────────────┐
 │                    │
 ▼                    ▼
Servo 2           LCD Displays
 │
 ▼
Grade A / Grade B

        │
        ▼

      ESP32
        │
        ▼
 ThingSpeak Cloud
```

---

# 🔄 System Workflow

1. User selects **Automatic Mode** using the rotary encoder.

2. Servo 1 retrieves a single egg from the roller.

3. Egg is placed on the weighing platform.

4. HX711 measures the egg weight.

5. Arduino classifies the egg:

| Weight | Classification |
|---------|---------------|
| 28–55 g | Grade A |
| 20–27 g | Grade B |
| <20 g | Reject |

6. Servo 2 rotates the platform to the proper collection bin.

7. LCD updates grading information.

8. DFPlayer announces the classification.

9. ESP32 uploads grading statistics to ThingSpeak.

10. System repeats until no eggs remain.

---

# ☁ IoT Dashboard

The ESP32 uploads the following information to ThingSpeak after each grading cycle:

- Total Eggs Sorted
- Grade A Count
- Grade B Count
- Sorting Duration

This enables remote monitoring of grading performance.

---

# 🔊 Voice Guidance

The DFPlayer Mini provides spoken feedback throughout the grading process.

Examples include:

- System Started
- Automatic Mode Activated
- Grade A Egg
- Grade B Egg
- Uploading Data
- Upload Complete

This improves usability for operators without requiring constant LCD monitoring.

---

# 🖥 User Interface

### Home Mode

Displays:

- Total eggs sorted
- Last sorting duration

Automation remains disabled.

---

### Automatic Mode

Displays:

- Current egg weight
- Current grading status
- Grade counters
- Live sorting process

---

# 🧪 Testing

Real eggs were intentionally **not used** during prototype validation to prevent accidental damage while refining the mechanical system.

Instead, plastic balls with equivalent egg weights were prepared:

| Test Object | Simulated Weight | Expected Grade |
|-------------|-----------------|---------------|
| Ball 1 | 37 g | Grade A |
| Ball 2 | 37 g | Grade A |
| Ball 3 | 24 g | Grade B |
| Ball 4 | 24 g | Grade B |

The prototype successfully:

- Correctly classified all test objects
- Routed each object to the proper collection area
- Updated LCD information
- Played voice notifications
- Uploaded grading statistics to ThingSpeak

---

# 📷 Project Gallery

## SmartEgg Grader Prototype

<img width="794" height="447" alt="w" src="https://github.com/user-attachments/assets/4968d2fe-5100-48c8-89b1-31f36b9768bd" />


*Front View*

---

<img width="781" height="440" alt="uuuu" src="https://github.com/user-attachments/assets/c397af7a-0a5e-4df0-a636-b4f02c255473" />


*Weight Measurement Platform*

---

<img width="781" height="440" alt="yyy" src="https://github.com/user-attachments/assets/89d5467f-cc4b-41d2-8452-3e79b074812c" />


*Side View*

---

<img width="660" height="371" alt="u" src="https://github.com/user-attachments/assets/18d8d620-cc3c-48e5-b929-b97ce0f1e10d" />


*Dual LCD User Interface*

---

<img width="725" height="408" alt="222" src="https://github.com/user-attachments/assets/ef3a993d-dc5d-4ba4-9c86-bfd039830115" />


*Automatic Egg Roller*

---

# 📊 ThingSpeak Dashboard

Displays:

- Total Eggs Sorted
- Grade A Count
- Grade B Count
- Sorting Duration

---

# 💻 Software

### Arduino Uno

Responsible for:

- Weight measurement
- Servo control
- LCD interface
- Rotary encoder
- DFPlayer Mini
- Classification algorithm

---

### ESP32

Responsible for:

- WiFi communication
- Serial communication with Arduino
- ThingSpeak data upload

---

# 🛠 Technologies Used

- Arduino IDE
- C++
- Arduino Uno
- ESP32
- HX711 Library
- LiquidCrystal_I2C
- Servo Library
- DFPlayer Mini
- ThingSpeak API

---

# 📁 Repository Structure

```
SmartEgg-Grader/
│
├── docs/
│   ├── Research Paper.pdf
│   ├── Block Diagram
│   ├── Flowchart
│
├── firmware/
│   ├── Arduino/
│   └── ESP32/
│
├── images/
│
├── README.md
```

---

# 👥 Contributors

Developed as a **three-member undergraduate embedded systems project** at **Mapúa University**.

**Project Contributions**

- Embedded firmware development
- Hardware integration
- Weight-based grading algorithm
- IoT cloud communication
- Mechanical automation
- LCD interface
- Voice feedback system
- System testing and validation

---

# 📄 Documentation

📘 Complete documentation:

**docs/**

Includes:

- Research paper
- Hardware block diagram
- Flowcharts
- Testing results
- Circuit diagrams
- Source code

---

# 📜 License

This project is intended for educational and research purposes.
