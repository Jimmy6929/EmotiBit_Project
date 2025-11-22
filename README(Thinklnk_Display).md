# 📟 ESP32 + ThinkInk E-Ink Clock (Hard-Coded Time)

This project drives a **200×200 Adafruit SSD1681 E-Ink display** using an **ESP32** (VSPI bus).
It displays a simple **HH:MM clock** with **no Wi-Fi or RTC** — the time is hard-coded and increments internally using `millis()`.

The e-ink panel refreshes **once per minute**, minimising ghosting and reducing power consumption.

---

## ✨ Features

* Displays a large, clear digital clock (`HH:MM`)
* Hard-coded starting time (no Wi-Fi, NTP, or RTC module required)
* Updates internal clock using `millis()`
* E-Ink refresh happens **once per minute** only
* Works on the **VSPI bus** of the ESP32
* Uses Adafruit GFX + EPD libraries

---

## 📦 Hardware Used

* **ESP32 (EmotiBit ESP32 or any Feather-style ESP32)**
* **Adafruit 200×200 SSD1681 E-Ink display (ThinkInk)**
* Jumper wires
* USB cable for programming

---

## 🖧 Wiring (VSPI Pins)

The code uses the **VSPI** hardware bus:

| Signal | ESP32 Pin | Description    |
| ------ | --------- | -------------- |
| SCK    | 18        | SPI clock      |
| MOSI   | 23        | SPI MOSI       |
| MISO   | 19        | SPI MISO       |
| CS     | 5         | Chip Select    |
| DC     | 16        | Data/Command   |
| RESET  | 17        | Display Reset  |
| BUSY   | 4         | Busy indicator |

---

## 🕒 Setting the Starting Time

Inside the code you can adjust:

```cpp
int hourNow = 12;   // starting hour (0–23)
int minuteNow = 00; // starting minute (0–59)
```

This is the time shown when the ESP32 boots.

The clock then advances every minute using `millis()`.

---

## 🔧 How It Works

### 1. **Internal Clock**

The `updateClock()` function checks if one minute (60,000 ms) has passed.
If so, it increments the minute and handles hour rollover.

### 2. **Screen Refresh**

Every minute, the display is updated via:

```cpp
display.display();
```

The screen shows:

* Large 4× text size
* Centered around (30, 80)

### 3. **Power Efficiency**

* No full-screen refreshes more often than needed
* E-Ink only draws power during refresh

---

## ▶️ Running the Code

1. Install these libraries in Arduino IDE:

   * **Adafruit_GFX**
   * **Adafruit_EPD**

2. Select your board:

   * *Tools → Board → ESP32 Dev Module*
     (or your specific EmotiBit/Feather ESP32)

3. Upload the sketch.

4. The display will show the time and update every minute.

---

## 📁 Code Overview

Main components of the sketch:

* 🕒 `updateClock()`
  Keeps track of elapsed minutes.

* 🖥️ `drawTime()`
  Draws the HH:MM string onto the e-ink display.

* ⚙️ `setup()`
  Initializes SPI + display and prints first time.

* 🔁 `loop()`
  Updates internal time and display at 60-second intervals.

