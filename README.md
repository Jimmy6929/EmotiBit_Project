# **EmotiBit + ThinkInk Clock (V1)**

A stable, low-power ESP32 firmware that lets the **EmotiBit biosignal module** run normally while independently driving a **ThinkInk SSD1681 e-ink display** to show a simple clock (HH:MM).
This Version 1 architecture ensures **zero interference** with EmotiBit’s sensors.

---

# ⭐ Project Overview

This project uses a **single ESP32** but splits functionality into two completely separate logical modules:

### **1. EmotiBit Core (unchanged)**

* Runs official EmotiBit firmware
* Manages PPG/EDA/temp sensors
* Handles power modes, sampling, button logic
* High-frequency sensor acquisition remains untouched

### **2. ClockDisplay Module (your code)**

* Uses a **dedicated VSPI bus**
* Drives a ThinkInk 200×200 e-ink display (SSD1681)
* Shows only **HH:MM** (starting from hard-coded time)
* Refreshes **once per minute**
* Lightweight, non-blocking loop

This separation guarantees that the display **never affects sensor performance**, timing, or power stability.

---

# 🔌 Hardware Setup

## **ThinkInk (SSD1681) Pin Map — VSPI (Final, Confirmed)**

These are the **correct**, **verified**, and **stable** pins for your ThinkInk display:

| Signal    | ESP32 Pin | Description                        |
| --------- | --------- | ---------------------------------- |
| **SCK**   | **18**    | SPI clock                          |
| **MOSI**  | **23**    | SPI Master → Display data          |
| **MISO**  | **19**    | Display → ESP32 data (rarely used) |
| **CS**    | **5**     | Chip Select                        |
| **DC**    | **16**    | Data/Command mode                  |
| **RESET** | **17**    | Display reset                      |
| **BUSY**  | **4**     | E-ink busy indicator               |

### Why these pins?

* They follow native **VSPI** hardware routing
* They avoid **all EmotiBit pins**
* They support fast, stable communication
* They prevent sensor-timing interference

---

# 🧩 Software Behavior

### ✔ Non-blocking Timekeeping

* Internal software clock using `millis()`
* No delays longer than **5 ms**
* Minutes increment based on elapsed time

### ✔ Safe Display Refresh Scheduler

* Redraw only when:
  ✔ display is not busy
  ✔ one minute has passed
* Ensures no blocking during EmotiBit sampling

### ✔ Simple Display Output

* White background
* Black “HH:MM”
* Full refresh only on minute change

### ❌ V1 intentionally *does not include*:

* Wi-Fi time sync
* Real RTC
* Biosignal icons or graphs
* Any EmotiBit → display interaction

This keeps V1 **stable** and **predictable**.

---

# ⚙ Stability Principles (V1 Rules)

These rules ensure EmotiBit sensor performance remains untouched:

* **Dedicated VSPI bus** for ThinkInk
* **Never block the loop**
* **Never refresh more frequently than 30–60 seconds**
* **Never share pins with EmotiBit systems**
* **Keep memory usage minimal**
* **Low current draw except during scheduled refresh**
* **Allow EmotiBit scheduler to run freely**

This is the entire philosophy of V1.

---

# 🧪 How to Use

1. Connect the display using the **confirmed pin map** above.
2. Flash the firmware to the **EmotiBit ESP32 Feather**.
3. Power the board via USB or regulated 3.3V.
4. The display will show the starting time (e.g., 12:00).
5. The display updates once per minute.
6. EmotiBit sensors continue running normally.

---

# 📚 Folder Structure (Recommended)

```
/src
  EmotiBitCore/     -> unmodified EmotiBit firmware
  ClockDisplay/     -> ThinkInk VSPI display logic
  main.cpp          -> high-level coordinator
/docs
  README.md
  wiring-diagram.png
  architecture-V1.png
```

---

# 🚀 Future V2+ Goals (Not in V1)

These are for later versions while keeping V1 stable:

* RTC-based real time
* Battery-aware refresh
* Stress/event icons using biosignal thresholds
* TinyML inference model
* Display-driven low-battery notifications
* On-device assistant logic

But all future features will maintain the **separation-of-concerns** that makes V1 stable.

---

# 📝 License

MIT License

---

# 🙌 Author

Jimmy Chu
AI-assisted firmware architecture by ChatGPT

Just tell me!

