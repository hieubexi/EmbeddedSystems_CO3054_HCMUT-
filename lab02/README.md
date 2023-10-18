| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

## folder contents

The project **lab2** contains one source file in C language [hello_world_main.c](main/lab2_scheduler.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both).

Below is short explanation of remaining files in the project folder.
```
├── CMakeLists.txt
├── pytest_hello_world.py      Python script used for automated testing
├── main
│   ├── CMakeLists.txt
│   └── lab2_scheduler.c
├── version
            This is the file contains version of program
└── README.md    
              This is the file you are currently reading
```

For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.
## Required environment
# Install
    * Download and install [Visual Studio Code](https://code.visualstudio.com/).
    * Open the **Extensions** view by clicking on the Extension icon in the Activity Bar on the side of Visual Studio Code or the **View: Extensions** command (shortcut: <kbd>⇧</kbd> <kbd>⌘</kbd> <kbd>X</kbd> or <kbd>Ctrl+Shift+X</kbd>.
    * Search the extension with any related keyword like `espressif`, `esp-idf`, `esp32`, `esp32s2`, etc.
    * Install the extension.


## How to run the project
We have two methods to run the project
1. Run using buttons provided by the application<br>
All of buttons are placed in the bottom of Visual Studio interface.
    * To build the project. Push the button ESP-IDF Build project
    * To flash to the device. Push the button ESP-IDF Flash device
    * To open monitor of device. Push the button ESP-IDF Monitor device
2. Run with commands
* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.


We will get back to you as soon as possible.
