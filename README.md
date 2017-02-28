# RTCtime by smz

An Arduino Real Time Clock library.  

This library makes using the DS1307 and DS3231 RTC module really easy and is compatible with the classic &lt;time.h&gt; datatypes and methods.

Forked from the excelent "Rtc by Makuna" library (https://github.com/Makuna/Rtc), this one uses different datatypes/classes for handling time. While the Makuna library uses the proprietary RtcDateTime class, this one uses the classic &lt;time.h&gt; datatypes/classes. There are also some minor differences with the names and types of a few methods. Extra features (_such as temperature reading, calibration, alarms and memory storage_) are available when supported by the module used.

 - Supports esp8266.
 - Supports SoftwareWire library.

## Installing this library (prefered method)
 - Using your Arduino IDE, open the Library Manager, search for "RTCtime by smz" and install.

## Installing this library from GitHub (alternative method)
 - Create a directory named "RTCtime" in your Arduino\libraries folder.
 - Clone this project into that folder.  
 - It should now be available in your Arduino IDE "Include Library" list.

## Examples

 - Examples will soon be added, please bear with me...

## Donating
If you like this library and you use it, please consider donating (_a "Donating" button will be soon added..._), but please __consider donating to the orignal devloper too__, as **he** did much of the work! 
