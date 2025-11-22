# **EmotiBit Sensor-Only Firmware (No Display, No Time Functions)**

This firmware runs an **EmotiBit ESP32** as a **pure sensor module**.
All display, timekeeping, and ThinkInk e-ink code has been removed to make the system lightweight and reliable for data collection, prototyping, and integration with external systems.

The sketch continuously:

* Starts and manages the EmotiBit firmware
* Reads **PPG (green)**, **EDA**, and **Thermopile temperature**
* Stores the most recent sample from each sensor
* Prints all sensor values over **USB Serial**
* Supports built-in EmotiBit button functions
* Keeps a fast, responsive main loop

No Wi-Fi, no Bluetooth, no e-ink display, no clocks, no SD writing — **just sensors + Serial output**.

---

## 🚀 Features

### ✔ Live Sensor Streaming

The code uses the EmotiBit library to read:

* **PPG_GREEN** – optical heart/PPG waveform
* **EDA** – electrodermal activity / skin conductance
* **THERMOPILE** – skin/ambient temperature

Values are updated continuously and streamed over USB.

### ✔ High-Speed Serial Output

Runs at:

```
2000000 baud
```

for fast, low-latency data output.

### ✔ EmotiBit Button Integration

The built-in button controls power modes:

* **Short press** → Toggle between:

  * `NORMAL_POWER`
  * `WIRELESS_OFF`
* **Long press** → Puts the EmotiBit into **sleep mode**

### ✔ Lightweight Main Loop

* No blocking delays
* No display refreshes
* No timing functions
* Only `delay(1)` to prevent CPU overload

Perfect for stable long-term logging.

---

## 📁 Project Structure

```
EmotiBit-SensorOnly/
│
├── EmotiBit_SensorOnly.ino   # Main code (provided in this repo)
└── README.md                 # This file
```

---

## 🔧 Hardware Requirements

* **EmotiBit ESP32 board**
* USB cable for power + Serial communication
* Computer or device that can read Serial data

No external display or SD card is required.

---

## 📦 Required Libraries

The following library must be installed:

* **EmotiBit Arduino library**
  (Available through EmotiBit’s GitHub or the Arduino Library Manager)

Arduino automatically includes:

* `Arduino.h`

---

## 🖥 Serial Output Format

Each loop prints the latest values:

```
PPG: <value>  EDA: <value>  TEMP: <value>
```

Example:

```
PPG: 14356.78  EDA: 0.215  TEMP: 32.47
```

You can pipe this into:

* Python applications
* Serial plotters
* Data loggers
* Custom PC dashboards
* Machine learning scripts

---

## ▶️ How to Use

1. Open the `.ino` file in Arduino IDE.
2. Select the correct board (EmotiBit ESP32) and port.
3. Upload the code.
4. Open **Serial Monitor** at **2,000,000 baud**.
5. Watch live sensor data stream in real-time.

---

## 🧠 How the Code Works (Summary)

1. **EmotiBit initialises**

   * Sensors activated
   * Internal buffers created

2. **Every loop:**

   * `emotibit.update()` manages internal tasks
   * `pollEmotiBitData()` reads sensor buffers
   * Latest values stored into `lastPPG`, `lastEDA`, `lastTempC`
   * Values printed to Serial
   * 1 ms delay to avoid CPU overload

3. **Button Press Logic:**

   * Toggles wireless power mode or enters sleep.

---

## 📌 Key Code Functions

| Function               | Description                                     |
| ---------------------- | ----------------------------------------------- |
| `pollEmotiBitData()`   | Reads new sensor data and updates latest values |
| `emotibit.update()`    | Required for EmotiBit internal processing       |
| `onShortButtonPress()` | Toggles power mode                              |
| `onLongButtonPress()`  | Puts device into sleep                          |
| `Serial.println()`     | Sends data to host computer                     |
