# Weather Station Project

## Overview
This project is part of a Faculty Development Program (FDP) workshop. The goal is to build a weather station using a DHT11 sensor, NodeMCU, and a 1.3-inch OLED screen.

## Materials
- DHT11 sensor: This sensor is used to measure temperature and humidity.
- NodeMCU: This is an open-source firmware and development kit that helps you to prototype your IoT product within a few Lua script lines.
- 1.3-inch OLED screen: This screen is used to display the temperature and humidity data collected by the DHT11 sensor.

## Setup
1. Connect the DHT11 sensor to the NodeMCU.
        GND---->GND
        VCC---->VIN
        DATA---->D3
2. Connect the NodeMCU to the OLED screen.
        GND----->GND
        VCC----->3V3
        SDA----->SDA(D2)
        SCL----->SCL(D1)
3. Upload the provided code to the NodeMCU using the Arduino IDE.

## Code
The code for this project is written in Arduino (C++). It reads the temperature and humidity data from the DHT11 sensor, and displays it on the OLED screen.

## Contributing
We welcome contributions to this project. If you have a feature request, bug report, or want to improve the code or documentation, please feel free to make a pull request or open an issue.

## License
This project is open source, under the MIT license.

## Contact
[www.ide](https://idealab.mec.ac.in/)

## Acknowledgements
We would like to thank all the students participating in this workshop. Your enthusiasm and hard work make this project possible.
