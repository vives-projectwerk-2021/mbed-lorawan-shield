# Pulu Main Firmware

## Setup

### LoRaWAN indoor gateway

Follow the steps from the [online documentation](https://www.thethingsindustries.com/docs/gateways/thethingsindoorgateway/).

## Compile

### Pulu Firmware Builder (faster and preferred)

The first time docker will pull [pulu-firmware-builder](https://github.com/vives-projectwerk-2021/pulu-firmware-builder/pkgs/container/pulu-firmware-builder). (2.3GB)

Building the firmware without version tags (defaults to latest)

```bash
make
```

Building the firmware with version tags for the firmware and/or firmware-builder

```bash
make VERSION=1.0.0 BUILDER_VERSION=1.1.0
```

### Mbed CLI (Windows only)

Use the mbed_installer which can be found [here](https://github.com/ARMmbed/mbed-cli-windows-installer/releases). (At the moment of developing, we used the most recent version 0.4.10)

We used conda as an environment management system to separate the dependencies of this project.

```bash
conda create --name projectwerk python=3.7
conda activate projectwerk
pip install mbed-cli
```

When having troubles with the GCC_ARM compiler, make sure you are using a version between 9 and 10.  
We used [9-2019-q4-major](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads/9-2019-q4-major) as compiler.

## Getting started

- Clone the project
- using mbed-cli
  - install library dependencies using `mbed deploy`
  - compile and flash using `mbed compile -f`
- using pulu-firmware-builder
  - compile using `make`
  - output binary in `/BUILD/`
- using github action releases
  - download the binary files from the github release
  - flash
