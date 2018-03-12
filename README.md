# RTCtime

**An Arduino Real Time Clock library.**

This library makes using modules based on the DS1307 and DS3231 RTC really simple. It is compatible with and is meant to leverage the standard C time library `<time.h>` API (datatypes and functions) as defined in [ISO/IEC 9899 (C90)](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf) and implemented in the AVR Std C runtime libray since version 2.0.0 (_available in the Arduino IDE since version 1.6.10_).

This work started as a fork of the excelent [Rtc by Makuna](https://github.com/Makuna/Rtc) library, but now supports the Std C API, while Rtc by Makuna uses a proprietary RtcDateTime class.

Extra features (_such as temperature reading, calibration, alarms and memory storage_) are available when supported by the underlying hardware.

 - Supports SoftwareWire library
 - Supports ESP8266 (_but see note below..._)

## Notes
- **This is a library for getting/setting the time from/to hardware RTC clocks**, using an API compatible with the Std C time library and the epoch defined in its AVR implementation, `2000-01-01T00:00:00Z`.

- **This is not** a library of time functions.

- Time functions are already available in the AVR Standard C runtime library and you can access them using `#include <time.h>` since Arduino IDE version 1.6.10. Those on a previous version of the IDE can probably use the [Arduino_RTC_Library](https://github.com/feilipu/Arduino_RTC_Library) (_originally by Michael Duane and now maintained by Phillip Stevens_) as a Std. C time compliant library.

- When using the AVR `<time.h>` Std C time library, you should run your RTC clock as UTC, and then use the `set_zone()` function to set your current timezone. Same thing with DST and the `set_dst()` function.

- Two methods have been added, `SetTimeUX()` and `GetTimeUX()`, that uses the Unix epoch, `1970-01-01T00:00:00Z`, instead of the AVR one. This can be useful when interfacing with Michael Margolis/Paul Stoffregen's [TimeLib, a.k.a. Time](https://github.com/PaulStoffregen/Time) library that doesn't follow the AVR convention and uses the Unix epoch. **Do not use the this methods if you are interfacing with the normal AVR Std C time library**.

- **ESP8266 support**. It has been [brought to my attention](https://github.com/smz/Arduino-RTCtime/issues/7) that the included examples do not compile for the ESP8266. The reason is that the ESP8266 time.h library is a minimal subset of the Std C time library and functions used by the examples are not available under it. Beside, the ESP8266 time.h uses the Unix epoch, `1970-01-01T00:00:00Z`, and not the AVR epoch, `2000-01-01T00:00:00Z`. You should then use the `GetTimeUX()` and `SetTimeUX()` methods of this library when interfacing with the ESP8266 time.h library. Anyway I think this library is still useful under the ESP8266 as a streamlined solution for interfacing with RTC clocks (_which is exactly its intent_) and thus I can still claim "ESP8266 support".

## Installation

### Install this library using the Arduino IDE (_prefered method_)
 - Using your Arduino IDE, open the Library Manager, search for "RTCtime by smz" and install.

### Install this library from GitHub (_alternative method_)
 - Create a directory named "RTCtime" in your Arduino\libraries folder.
 - Clone this project into that folder. 
 - It should now be available in your Arduino IDE "Include Library" list.

## Examples

 - There are a couple of commented examples in the `./examples` folder. You might try them and use them as a reference, until I write a more formal API documentation (_See note above for ESP8266_)

## Donating
If you like this library and you use it, please consider donating, but please __consider donating to the orignal devloper too__, as **he** did much of the work! 

[![Donate](http://img.shields.io/paypal/donate.png?color=yellow)](https://www.paypal.me/SergioManzi)
