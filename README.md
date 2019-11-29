# AppointmentAlertSystem

## Installation
- Make sure you system supports:
  - stdio.h, stdlib.h, unistd.h, getopt.h
  - iostream, sstream, string (C++ standard libraries)
  - libcurl
    - Mac: comes pre-installed
    - Windows: download libcurl

- Program must be ran with a curl linker
  - On Mac:
    - xCode: Build Settings->Other Linker Flags
      - Add `-lcurl` linker flag
