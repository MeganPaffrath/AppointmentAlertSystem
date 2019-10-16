# AppointmentAlertSystem

## Installation
- Make sure you system supports:
  - stdio.h, stdlib.h, unistd.h
  - iostream, sstream, string (C++ standard libraries)
  - libcurl
    - Mac: comes pre-installed
    - Windows: download libcurl

- Program must be ran with a curl linker
  - On Mac:
    - (Currently having issues w/ new Catalina update)
    - xCode: Build Settings->Other Linker Flags
      - Add `-lcurl` linker flag
      - Product->Scheme->edit scheme
        - Under "Options"
          - Check: "Use custom working directory"
          - Make src file the working directory
  - On Windows
