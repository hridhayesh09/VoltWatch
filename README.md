Overview
VoltWatch is a custom-designed PCB system that monitors residential power quality in real time, detects voltage surges, and sends alerts before equipment damage occurs. Inspired by a personal experience where a thunderstorm surge destroyed a pair of speakers.

## Hardware
- ESP32 WROOM-32 microcontroller
- ZMPT101B AC voltage sensor
- Custom PCB designed in KiCad (in progress)

## Stack
- Firmware: Embedded C on ESP32 (PlatformIO)
- Backend: Python Flask + SQLite
- Alerts: Twilio SMS (coming soon)
- Dashboard: React (coming soon)
- ML: scikit-learn anomaly detection (coming soon)

## How It Works
The ESP32 reads voltage data from the ZMPT101B sensor 1000 times per second, calculates peak-to-peak values, detects surge events, and sends timestamped data to a Flask backend over WiFi for storage and analysis.

