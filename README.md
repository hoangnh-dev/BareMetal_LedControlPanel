# BareMetal_LedControlPanel
## Overview
This project implements multi-state LED control on STM32 microcontrollers using user push-buttons and UART commands. Built specifically as a bare-metal C learning project, all peripheral drivers (GPIO, RCC, UART, ...) are developed directly at the register level without using vendor HAL libraries.
> **Note:** As this is a self-study project, some modular components and placeholder code are intentionally included for future experimentation and feature expansion.
## Features
- Button: Switch LED modes via EXTI interrupt
- UART: Show control panel menu and set LED modes via commands
## Hardware Configuration
* **MCU:** [STM32F103C8T6 (Blue Pill)](https://github.com/WeActStudio/BluePill-Plus)
### Pinout Mapping

| Function   | Pin | Mode               |
|------------|-----|--------------------|
| LED        | PB2 | Output, Push-Pull  |
| Button     | PA0 | Input, EXTI0       |
| UART TX    | PA9 | Alternate Function |
| UART RX    | PA10| Input Floating     |
---
## Software & Tools

* **IDE / Code Editor:** VS Code (Windows)
* **Compiler / Toolchain:** Arm GNU Toolchain (`arm-none-eabi-gcc` v15.3)
* **Build System:** GNU Make (`make` v4.4.1)
* **Flash Utility:** ST-Link Tools (`st-flash` v1.8.0)
* **Serial Terminal:** PuTTY (for UART debugging and control panel interface)

## How to Build & Flash (via VS Code Terminal)
Ensure you have the following tools added to your system `PATH` (Compiler, Build System, Flash Utility).
**Build Project:**
```powershell
make
```
**Build Project:**
```powershell
make flash
```
**Open UART Control Panel:**
- Launch PuTTY
- Select Serial, set your COM Port (e.g., COM7) and Baud Rate (e.g., 115200).
- Open connection to interact with the control panel or use user button to switch LED mode

**UART Command Interface**
```text
====== MENU ======
[1] 1 - OFF
[2] 2 - ON
[3] 3 - Blink slow
[4] 4 - Blink fast
==================
> Enter your selection:
```
