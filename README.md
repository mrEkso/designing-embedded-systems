<!--
	README for `designing-embedded-systems`
	Style: Davyd Okaianchenko (professional, engineering-focused, minimal)
-->

# Designing Embedded Systems

[![License](https://img.shields.io/badge/license-Multiple%20%2F%20See%20folders-lightgrey)](./vs_6)
[![Platform](https://img.shields.io/badge/target-STM32C0%20series-blue)](#)

Compact repository containing coursework and reference material for embedded systems design based on the STM32C0 family. This repository collects project sources, HAL drivers, FreeRTOS middleware, and build artifacts used for study, experimentation, and demonstration.

## Purpose

This repository is a technical sandbox and reference implementation that demonstrates practical embedded system design patterns for the STM32C0 microcontrollers: partitioning (drivers/middleware/application), build and flashing workflows, and integration with RTOS and peripheral HALs.

Values: clarity, predictability, scalability.

## Contents (high level)

- `vs_6/` — primary project workspace (source code, IDE artifacts, Makefile, linker script).
- `Core/` — application `Src` and `Inc` (FreeRTOS-based app and support code).
- `Drivers/` — STM32 HAL and BSP drivers.
- `Middlewares/` — third-party stacks (FreeRTOS, QP/C, etc.).
- `build/` — compiled object/assembly listings and automatically generated build outputs.
- `openocd.cfg` — OpenOCD configuration for debugging/flashing.

See the `vs_6` folder for the working Makefile and build targets.

## Quick start — build and flash (Windows / PowerShell)

Prerequisites (examples):

- GNU Arm Embedded Toolchain (gcc-arm-none-eabi)
- Make (GNU Make)
- OpenOCD (for flashing/debugging)
- ST-Link or compatible SWD probe

1. Open PowerShell in repository root.
2. Build the project (working directory: `vs_6`):

```powershell
cd vs_6
make all
```

3. Flash via OpenOCD (example):

```powershell
openocd -f ..\openocd.cfg -c "program build\projectName.elf verify reset exit"
```

Notes:

- Replace `projectName.elf` with the produced ELF in `vs_6/build` (Make outputs vary by configuration).
- If using an IDE (STM32CubeIDE), open the `vs_6.ioc` in the `vs_6` folder for project import.

## Project layout (recommended)

Keep source separation strict:

- Drivers (HAL): low-level peripheral code.
- Core application: RTOS setup, tasks, application logic.
- Middlewares: FreeRTOS and any protocol stacks.

Example: `vs_6/Core/Src/main.c` initializes peripherals, starts FreeRTOS scheduler and registers tasks.

## Development workflow and conventions

- Use Makefile targets in `vs_6/Makefile` for deterministic builds.
- Keep generated artifacts out of source control (they are stored under `build/` by local builds).
- Prefer descriptive commit messages and keep changes modular (single responsibility per change).

### Debugging

- Use OpenOCD + GDB for step-through debugging. `openocd.cfg` contains a recommended target setup.
- Use `arm-none-eabi-gdb` with the ELF file in `vs_6/build` to set breakpoints and inspect memory/registers.

## Tests & CI

This repository contains course and demo code; no automated CI is configured by default. Suggested CI checks:

- Validate build with gcc-arm-none-eabi in a matrix job.
- Lint C code with `clang-format`/`clang-tidy` rules suitable for embedded (optional).

## Licensing

Third-party components include their own licenses (see `vs_6/Drivers` and `vs_6/Middlewares` folders). The project itself does not currently assert a single license at the root; consult subfolders for specific license files.

## Contributing

Contributions should follow these rules:

- Target a single, well-scoped change per commit.
- Include build/test instructions for changes affecting build or hardware.
- When adding third-party code, include its original license in the target folder.

To propose larger changes, open an issue with a short technical description, the goal, and a minimal reproduction or patch.

## Contact

Repository maintenance and style by Davyd Okaianchenko. For technical questions, open issues in this repository.

**GitHub:** [@mrEkso](https://github.com/mrEkso)  
**LinkedIn:** [Davyd Okaianchenko](https://www.linkedin.com/in/davyd-okaianchenko/)