# Custom RTOS for ESP32

## Overview
This is a basic RTOS implementation for the ESP32, written from scratch without relying on FreeRTOS or other RTOS libraries. It includes a simple task scheduler and timer-based task switching.

## Features
- Custom task management system
- Timer-based task switching using GPTimer
- Support for multiple tasks
- Interrupt handling for context switching

## Project Structure
```
MY_RTOS_ESP32/
│── inc/                # Header files
│── src/                # Source files
│   ├── main.c          # Entry point
│   ├── scheduler.c     # Task scheduler
│   ├── task.c          # Task definitions
│   ├── timer.c         # Timer setup for task switching
│── CMakeLists.txt      # CMake configuration
│── sdkconfig           # ESP-IDF configuration
│── README.md           # Project documentation
```

## Getting Started
### Prerequisites
- ESP32 board
- ESP-IDF v5.4
- GCC toolchain for ESP32
- `idf.py` for building and flashing the firmware

### Build and Flash
```sh
idf.py build flash monitor
```

### Expected Output
After flashing, the ESP32 should start executing the custom RTOS, and tasks should switch periodically. Example logs:
```
I (274) RTOS: Starting custom RTOS...
I (274) TASK: Initializing tasks...
I (284) GPTimer: GPTimer started with 1000000 us interval
I (1284) Scheduler: Switching to Task 1
I (1284) Task2: Executing Task 2...
I (1414) Task2: Task 2 completed.
I (2284) Scheduler: Switching to Task 0
I (2284) Task1: Executing Task 1...
```

## Known Issues
**Guru Meditation Error**:
- This error might occur due to improper stack handling during context switching.
- If you experience this, check the `task_switch()` function and ensure proper stack management.
- Increasing stack size in `sdkconfig` may help prevent stack overflows.

## Contributing
Feel free to contribute by improving the scheduler, adding task priorities, or implementing additional RTOS features.

## License
MIT License

