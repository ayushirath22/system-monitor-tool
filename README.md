# System Monitor Tool

A lightweight "System Monitoring Tool" built in *C++*, inspired by the `top` command in *Linux*.  
It displays real-time information such as:
- Active processes
- CPU usage (simulated in WSL environment)
- Memory usage
- Option to *kill processes* by PID
- Auto-refreshing live terminal interface

This project demonstrates usage of **Linux system programming**, **process management**, and **terminal-based UI handling**.

---

## 🚀 Features

| Feature | Description |
|--------|-------------|
| Process Listing | Shows current running processes with PID and names |
| CPU & Memory Usage | Displays usage stats for each process *(simulated in WSL)* |
| Sorting | Processes automatically sorted by CPU and memory usage |
| Kill Process | Allows user to manually terminate any process by entering PID |
| Real-Time Refresh | Screen updates every second to show latest data |

---

## ⚙️ Why CPU/MEM Usage is Simulated?

The project was developed and tested on **WSL (Windows Subsystem for Linux)**.  
WSL does **not provide real-time per-process CPU usage** through `ps`, unlike a full Linux kernel.  
So to simulate realistic dynamic behavior, small fluctuating values are generated.

If run on a real Linux environment (Ubuntu dual boot / VM), it will display actual usage.

---

## 🛠️ How to Compile & Run

### **Step 1: Clone the repository**
```bash
git clone https://github.com/YOUR-USERNAME/system-monitor-tool.git
cd system-monitor-tool

g++ src/main.cpp src/process_list.cpp src/control.cpp src/refresh.cpp -o build/system_monitor
./build/system_monitor
