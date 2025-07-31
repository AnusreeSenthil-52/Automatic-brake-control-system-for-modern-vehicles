# 🚗 Automatic-brake-control-system-for-modern-vehicles
  A safety-focused embedded system that automatically controls braking based on real-time distance and speed sensing. Used Arduino and ultrasonic sensor to measure proximity and activate emergency brakes. MATLAB was used to plot real-time graphs of distance and speed.

## 🔧 Components Used
- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- L293D Motor Driver IC
- 2 DC Motors
- Buzzer
- LCD Display(16x2 I2C)
- Wires, Chassis Kit, 9V Battery
- Breadboard

## 🧠 Working Principle
- Arduino UNO measures distance using the ultrasonic sensor.
- If distance < threshold, buzzer alerts and vehicle reduces its speed and stops.
- LCD displays the speed, distance and status of the vehicle (danger/safe)
- Distance data is also sent to MATLAB via serial for plotting speed and distance in real time.

## 🧾 Files Included
- `Arduinocode.ino` – Arduino code
- `Matlsbcode.m` – MATLAB code to filter and plot distance/speed
- `Snapshots of project` – Images of hardware and output plots

## Skills gained
- Embedded C (Arduino IDE)
- Signal processing (MATLAB)
- Sensor Integration
  
## 📌 Future Improvements
- Add obstacle memory (map creation)
- Implement machine learning for smarter navigation

---

