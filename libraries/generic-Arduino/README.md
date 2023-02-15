# generic-Arduino

[![GitHub license](https://img.shields.io/github/license/noah1510/generic-Arduino.svg)](https://github.com/noah1510/generic-Arduino/blob/master/License)
[![stable release](https://img.shields.io/github/v/release/noah1510/generic-Arduino.svg)](https://GitHub.com/noah1510/generic-Arduino/releases/)
[![arduino-library-badge](https://www.ardu-badge.com/badge/generic-Arduino.svg?)](https://www.ardu-badge.com/generic-Arduino)

This library provides a generic abstraction over Arduino.h, to support more platforms.
Simply include `generic-Arduino.hpp` and you good to go.

There is also a generic SPI implementation.
You can use it by including `SPIAbstraction.hpp`.
The interface is similar to the interface of `SPI.h` from the ES but works even when there is not SPI hardware.
