| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# Folder contents
The project **lab3** contains 4 source files in C language 

* Prioritized scheduling with time slicing [main.c](Prioritized_scheduling_time_slicing\main\main.c). The file is located in folder [main](Prioritized_scheduling_time_slicing\main).
* Prioritized scheduling without time slicing [main.c](Prioritized_scheduling_without_time_slicing\main\main.c). The file is located in folder [main](Prioritized_scheduling_without_time_slicing\main).
* Co-operative Scheduling [main.c](Co-operative_Scheduling\main\Co-operative_Scheduling.c). The file is located in folder [main](Co-operative_Scheduling\main).
* Extra exercise. CPU Utilization [main.c](cpuUtilization\main\main.c). The file is located in folder [main](cpuUtilization\main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both).

Below is short explanation of remaining files in the project folder.
```
├── CMakeLists.txt
├── pytest_hello_world.py      Python script used for automated testing
├── main
│   ├── CMakeLists.txt
│   └── lab2_scheduler.c
├── version
│             This is the file contains version of program
└── README.md    
              This is the file you are currently reading
```

For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.
# Required environment
## Install
1. Download and install [Visual Studio Code](https://code.visualstudio.com/).
2. Open the **Extensions** view by clicking on the Extension icon in the Activity Bar on the side of Visual Studio Code or the **View: Extensions** command (shortcut: <kbd>⇧</kbd> <kbd>⌘</kbd> <kbd>X</kbd> or <kbd>Ctrl+Shift+X</kbd>.
3. Search the extension with any related keyword like `espressif`, `esp-idf`, `esp32`, `esp32s2`, etc.
4. Install the extension. You can follow the instructions [HERE](https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md).
# How to run the project
We have two methods to run the project
1. Run using buttons provided by the application<br>
All of buttons are placed in the bottom of Visual Studio interface.
```
    * Build the project. Push the button ESP-IDF Build project
    * Flash to the device. Push the button ESP-IDF Flash device
    * Open monitor of device. Push the button ESP-IDF Monitor device
```
2. Run with commands
```
    * Build the project. `idf.py build`
    * Flash to the device. `idf.py flash`
    * Open monitor of device. `idf.py monitor`
```
or you can just run multiple commands `idf.py build flash monitor`.

* Program upload failure
    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.
We will get back to you as soon as possible.
