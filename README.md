# Automatic Cat Feeder

## Requirements
- ESP32-S2
- ESP32-S2-Saola-1 development board
- Python 3.10 or newer:
    [Download](https://www.python.org/downloads/)
- ESP-IDF Installation Manager (EIM) to install ESP-IDF, build tools, and toolchain:
    [Get Started Documentation](https://docs.espressif.com/projects/esp-idf/en/v6.0/esp32s2/get-started/index.html)
    - Our specific setup follows:
        - Install EIM with Package Manager Homebrew: CLI
        - Install ESP-IDF Using EIM: Online Installation using EIM CLI
        - Build Your First Project: Build from Command Line


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

#### Adding External Components
- Add component to idf_component.yml file:
    ```
    idf.py add-dependency <external component>
    ```
- Execute the reconfigure command:
    ```
    idf.py reconfigure
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
