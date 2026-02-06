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
- Make the configuration menu:
    ```
    make menuconfig
    ```
- Flash the ESP8266:
    ```
    make flash
    ```
- Monitoring activity:
    ```
    make monitor
    ```
- Cleanup:
    ```
    make clean
    ```

#### Useful Commands
- Finding what port our device is using (Mac):
    ```
    ls /dev/tty*
    ```
- Temporarily overiding sdkconfig python configuration:
    ```
    CONFIG_SDK_PYTHON=python3
    ```

#### Documents
- [LOLIN D1 mini board](https://www.wemos.cc/en/latest/d1/d1_mini.html)
- [LOLIN D1 mini board schema](https://www.wemos.cc/en/latest/_static/files/sch_d1_mini_v4.0.0.pdf)
- [ESP8266 Datasheet](https://documentation.espressif.com/0a-esp8266ex_datasheet_en.pdf)
- [ESP8266 12E Chip Pinout or the Wemos D1 Mini Pinout??](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)