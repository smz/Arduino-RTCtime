# RTCtime by smz

An Arduino Real Time Clock library.  

This library makes using the DS1307 and DS3231 RTC modules really easy and is compatible with the standard C time library `<time.h>` API (datatypes and functions) as defined in [ISO/IEC 9899 (C90)](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf) and implemented in the AVR Std C libray which is part of the Arduino IDE.

This work started as a fork of the excelent "Rtc by Makuna" library (https://github.com/Makuna/Rtc), but now supports the Std C API, while Makuna library uses a proprietary RtcDateTime class. There are also minor differences with the names and types of a few methods. Extra features (_such as temperature reading, calibration, alarms and memory storage_) are available when supported by the hardware you're using.

 - Supports esp8266
 - Supports SoftwareWire library

## Please note:
- This is **not a library of time functions**.

- This library is for **setting/getting time from hardware RTC clocks** (_and some extra stuff..._) in ways that are consistent with the Std C time library and the epoch defined in its AVR implementation, `2000-01-01T00:00:00Z`.

- Time functions are already defined in the AVR Std C library and you can access them using `#include <time.h>` since Arduino IDE version 1.6.10. Those on a previous version of the IDE can probably use the [Arduino_RTC_Library](https://github.com/feilipu/Arduino_RTC_Library) as a Std. C time compliant library.

- When using the Std C time library, you are supposed to have your RTC clock running as UTC, and then use the Std C `set_zone()` function to set your current timezone. Same thing with DST and the `set_dst()` function.

- Two methods have been added, `SetTimeUX()` and `GetTimeUX()`, that uses the Unix epoch, `1970-01-01T00:00:00Z`, instead of the AVR one. Those two functions potentially makes this library useful when using Michael Margolis/Paul Stoffregen's [TimeLib, a.k.a. Time](https://github.com/PaulStoffregen/Time) library that do not follow the Std C API but uses the Unix epoch (_untested by me, at this time, use at your own risk..._). **Do not use the** `UX` **functions if you use the Std C time library**.

## Install this library using the Arduino IDE (_prefered method_)
 - ~~Using your Arduino IDE, open the Library Manager, search for "RTCtime by smz" and install.~~ *

This method is not available yet: it will be available when the library will reach its first official release

## Install this library from GitHub (_alternative method_)
 - Create a directory named "RTCtime" in your Arduino\libraries folder.
 - Clone this project into that folder.  
 - It should now be available in your Arduino IDE "Include Library" list.

## Examples

 - There are a couple of commented examples in the `./examples` folder. You might try them and use them as a reference, until I write a more formal API documentation

## Donating
If you like this library and you use it, please consider donating, but please __consider donating to the orignal devloper too__, as **he** did much of the work! 

[![Donate](http://img.shields.io/paypal/donate.png?color=yellow)](https://www.paypal.me/SergioManzi)
