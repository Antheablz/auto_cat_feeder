# Automatic Cat Feeder

## Requirements
- Python 2.7:
    [Download](https://www.python.org/downloads/release/python-2718/)
- Toolchain Setup:
    [Instructions & Download](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/macos-setup.html)
- ESP8266_RTOS_SDK:
    [Instructions & Download](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#start-a-project)
    - When installing the reqirements, use the following commands inside the SDk directory:
        ```
        python -m pip install -U pip pyelftools==0.22
        python -m pip install --user -r requirements.txt
        ```
    - Paths for .bash_profile:
        ```
        export PATH=$PATH:$HOME/esp/xtensa-lx106-elf/bin
        export IDF_PATH=~/esp/ESP8266_RTOS_SDK
        ```


## Getting Started

#### Compilation and Execution
- Set target:
    ```
    idf.py set-target esp32s2
    ```
- Make the configuration menu:
    ```
    idf.py menuconfig
    ```
- Build the project:
    ```
    idf.py build
    ```
- Flash onto the device:
    ```
    idf.py -p PORT flash
    ```
- Monitoring activity:
    ```
    idf.py -p PORT monitor
    ```
- Cleanup:
    ```
    idf.py clean
    ```

#### Useful Commands
- Finding what port our device is using (Mac):
    ```
    ls /dev/tty*
    ```
- Activate the environment:
    ```
    source "/Users/antheablais/.espressif/tools/activate_idf_v6.0.sh"
    ```

#### Mosquitto
- starting and stopping Mosquitto:
    ```
    brew services start mosquitto
    brew services stop mosquitto
    ```
- where the mosquito.conf file is located (on my mac)
```
/usr/local/etc/mosquitto/mosquitto.conf
```

#### Documents
- [ESP32-S2-Saola-1 board](https://docs.espressif.com/projects/esp-idf/en/v4.3/esp32s2/hw-reference/esp32s2/user-guide-saola-1-v1.2.html)
- [ESP32-S2-Saola-1 board schematics](https://dl.espressif.com/dl/schematics/ESP32-S2-SAOLA-1_V1.1_schematics.pdf)
- [ESP32-S2-WROVER Datasheet](https://documentation.espressif.com/esp32-s2-wrover_esp32-s2-wrover-i_datasheet_en.pdf)
- [ESP32-S2 Get Started](https://docs.espressif.com/projects/esp-idf/en/v6.0/esp32s2/get-started/index.html)


install EIM with Package Manager Homebrew: CLI
Install ESP-IDF Using EIM: Online Installation using EIM CLI
Build Your First Project: Build from Command Line

After installing the ESP-IDF with the CLI, must activate the environment using:
    ```
    source "/Users/antheablais/.espressif/tools/activate_idf_v6.0.sh"
    ```