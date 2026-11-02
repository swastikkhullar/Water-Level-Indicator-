#  Water Level Indicator (Arduino UNO R4 WiFi + Ultrasonic Sensor)

A simple, low-cost water level indicator built with an **Arduino UNO R4 WiFi**, an **ultrasonic distance sensor**, a **16×2 LCD** and two **LEDs**. The LCD shows how full a container is as a percentage, the **green LED** tells you it's time to refill, and the **red LED** tells you the container is full.



>  **Full demo video:** [`media/demo.mp4`](media/demo.mp4)

---

##  Features

- Contactless water level measurement using an ultrasonic sensor
- Live level shown as a **percentage** on a 16×2 LCD
-  **Green LED** → level is low, container needs to be filled
-  **Red LED** → container has reached the full level
- once the red LED turns on, it stays on until the level drops below the low threshold
- Calibration sketch included to measure your own container's "empty" and "full" distances

---

##  How It Works

The ultrasonic sensor is mounted at the top of the container, pointing down at the water surface. It sends a pulse and measures the time taken for the echo to return:

```
distance (cm) = (echo time in µs × 0.0343) / 2
```

The distance is then converted into a fill percentage using two calibrated values:

```
fill height = empty_dis − measured distance
percent     = fill height / (empty_dis − full_dis) × 100
```

| Constant     | Value (in code) | Meaning                                              |
|--------------|-----------------|------------------------------------------------------|
| `empty_dis`  | `12.88` cm      | Sensor-to-bottom distance when the container is empty |
| `full_dis`   | `2.00` cm       | Sensor-to-water distance when the container is full   |

>  These two values are specific to *my* container. Use the calibration sketch (below) to measure yours.

### LED logic

| Water level                                   |  Green |  Red |
|-----------------------------------------------|:--------:|:------:|
| Below **25 %** (low – needs filling)          | ON       | OFF    |
| Rising from 25 % to 90 %                      | ON       | OFF    |
| Reaches **90 %** (full)                       | OFF      | ON     |
| Falling from 90 % down towards 25 %           | OFF      | ON     |
| Drops below **25 %** again                    | ON       | OFF    |

The two thresholds are plain numbers in the sketch (`25` and `90`), so you can change them easily to suit your tank.

---

##  Components Required

| Qty | Component                                   | Notes                                         |
|-----|---------------------------------------------|-----------------------------------------------|
| 1   | Arduino UNO R4 WiFi                         | Any 5 V Arduino with enough pins will also work |
| 1   | Ultrasonic distance sensor (HC-SR04 type)   | Uses TRIG + ECHO pins                          |
| 1   | 16×2 LCD (HD44780, parallel interface)      | Used in 4-bit mode                             |
| 1   | 10 kΩ potentiometer                         | LCD contrast adjustment                        |
| 1   | Green LED                                   | "Fill the container" indicator                 |
| 1   | Red LED                                     | "Container full" indicator                     |
| 2   | Resistors (220 Ω – 330 Ω)                   | One in series with each LED                    |
| 1   | Breadboard + jumper wires                   |                                                |
| 1   | USB-C cable                                 | Power + programming                            |




##  Known Limitations

- Accuracy depends on the sensor being mounted **level and still**; ripples, foam or a tilted sensor will make the reading jump
- Most ultrasonic sensors cannot measure reliably closer than ~2 cm, which is why `full_dis` is set at 2 cm
- The percentage is not clamped to 0–100 %, so you may briefly see slightly out-of-range values
- If the device is powered on while the level is *between* 25 % and 90 %, the red LED turns on until the level next drops below 25 %
- The main loop blocks while waiting for the level to rise above 90 %, so it is not yet suitable for adding other tasks

---

##  Future Improvements

The UNO R4 WiFi has built-in Wi-Fi, which this version does not use yet. Ideas for the next version:

- [ ] Send the water level to a phone/web dashboard (e.g. a simple web page hosted on the board)
- [ ] Notifications when the container is full or nearly empty
- [ ] Buzzer alert
- [ ] Relay to control a pump automatically
- [ ] Averaging/filtering of readings for steadier values
- [ ] Waterproof sensor and a 3D-printed mount

---

##  Contributing

Suggestions and pull requests are welcome. If you find a bug or have an improvement, please open an issue.



If this project helped you, consider giving it a ⭐!
