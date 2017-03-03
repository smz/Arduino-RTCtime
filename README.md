# RTCtime by smz

An Arduino Real Time Clock library.  

This library makes using the DS1307 and DS3231 RTC modules really easy and is compatible with the classic &lt;time.h&gt; datatypes and methods.

Forked from the excelent "Rtc by Makuna" library (https://github.com/Makuna/Rtc), this one uses different datatypes/classes for handling time. While the Makuna library uses the proprietary RtcDateTime class, this one uses the classic &lt;time.h&gt; datatypes/classes. There are also some minor differences with the names and types of a few methods. Extra features (_such as temperature reading, calibration, alarms and memory storage_) are available when supported by the module used.

 - Supports esp8266 (*hopefuly, untested*)
 - Supports SoftwareWire library (*hopefuly, untested*)

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
