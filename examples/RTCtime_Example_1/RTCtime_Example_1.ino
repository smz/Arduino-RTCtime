
// ------> V E R Y   I M P O R T A N T !  <------
// CONNECTIONS:
//
// DS3231/DS1307 SDA --> SDA
// DS3231/DS1307 SCL --> SCL
// DS3231/DS1307 VCC --> 5V (can be also 3.3V for DS3231)
// DS3231/DS1307 GND --> GND


// ------> V E R Y   I M P O R T A N T !  <------
// Uncomment the #define here below if you use a DS3231 RTC
// or comment it if you use a DS1307
// #define DS3231


// ------> I M P O R T A N T !  <------
// DEBUG - Uncomment  if you want to have more information about what's going on...
// #define DEBUG


// ------> I M P O R T A N T !  <------
// Adjust SERIAL_SPEED to your needs:
// The default is 9600, but you probably can increase it in your IDE
// and set it here accordingly
#define SERIAL_SPEED 9600



// ------> I M P O R T A N T !  <------
// Uncomment the #define here below if you want to use
// the SoftwareWire library (... and remember to install it!)
// #define RTC_SOFTWARE_WIRE


// ------> I M P O R T A N T !  <------
// We can set our Time Zone and initialize the <time.h> library with it
// Initialization performed later, using the standard set_zone() function.
// set_zone() takes its argument as seconds (positive or negative)
// but using hours is easier (unless you live in a country using a fractional Time Zone)
#define MY_TIMEZONE 1   // I'm in Europe...
#define MY_TIMEZONE_IN_SECONDS (MY_TIMEZONE * ONE_HOUR)


//===============================================================================================================//



// We NEED the standard C time library...
#include <time.h>


// Here where we instantiate our "Rtc" object
// In your project you can get rid of all this stuff, if you want, and just #include and initialize what you need
#ifndef RTC_SOFTWARE_WIRE
  #include <Wire.h>
  #ifdef DS3231
    #include <RtcDS3231.h>
    RtcDS3231<TwoWire> Rtc(Wire);
  #else
    #include <RtcDS1307.h>
    RtcDS1307<TwoWire> Rtc(Wire);
  #endif
#else
  #include <SoftwareWire.h>
  #ifdef DS3231
    #include <RtcDS3231.h>
    SoftwareWire myWire(SDA, SCL);
    RtcDS3231<SoftwareWire> Rtc(myWire);
  #else
    #include <RtcDS1307.h>
    SoftwareWire myWire(SDA, SCL);
    RtcDS1307<SoftwareWire> Rtc(myWire);
  #endif
#endif


// Scheduler:
// We will use this in the loop() to read our RTC every so much (interval) milliseconds *without using a delay()*
// We CAN'T read it at every loop: the chip takes it time to "settle".
// 100 milliseconds *seems* to work, but 1000 milliseconds is fair enough (after all the RTC gives the time with a 1 second precision...)
unsigned long prev_millis = 0;
unsigned long interval = 1000;


// Support stuff for debug...
#ifdef DEBUG
  #define DUMP(x)           \
    Serial.print(#x);       \
    Serial.print(F(" = ")); \
    Serial.println(x);
  #define DUMP_TM(x)  \
    DUMP(x.tm_year);  \
    DUMP(x.tm_mon);   \
    DUMP(x.tm_mday);  \
    DUMP(x.tm_hour);  \
    DUMP(x.tm_min);   \
    DUMP(x.tm_sec);   \
    DUMP(x.tm_isdst); \
    DUMP(x.tm_yday);  \
    DUMP(x.tm_wday);
  unsigned long loops = 0;
#endif


// SETUP
void setup() {

  // Setup Serial
  Serial.begin(SERIAL_SPEED);
  #ifdef DEBUG
    Serial.println(F("Setup started."));
  #endif

  // Setup RTC
  Rtc.Begin();
  set_zone(MY_TIMEZONE_IN_SECONDS);

  // Here we convert the __DATE__ and __TIME__ preprocessor macros to a "time_t value"
  // and then to a "struct tm object" to initialize the RTC with it in case it is "older" than
  // the compile time (i.e: it was wrongly set. But your PC clock might be wrong too!)
  // or in case it is invalid.
  // This is *very* crude, it would be MUCH better to take the time from a reliable
  // source (GPS or NTP), or even set it "by hand", but -hey!-, this is just an example!!
  // N.B.: We always set the RTC to the compile time when we are debugging.
  #define COMPILE_DATE_TIME (__DATE__ " " __TIME__)
  char* compile_date_time = COMPILE_DATE_TIME;
  time_t compiled_time_t = str20ToTime(compile_date_time);  // str20ToTime converts a 20 chars date and time string to a time_t (like) value (See it in RtcUtility.h)
  compiled_time_t += MY_TIMEZONE_IN_SECONDS;                // ... but we must correct for our Time Zone as str20ToTime() doesn't do that!
  struct tm compiled_time_tm;
  gmtime_r(&compiled_time_t, &compiled_time_tm);            // We put our compile time into a "struct tm" object too...

#ifdef DEBUG
  DUMP(compile_date_time);
  DUMP(compiled_time_t);
  DUMP_TM(compiled_time_tm);
  char* compiled_time_string = ctime(&compiled_time_t);
  DUMP(compiled_time_string);
  time_t offset = mk_gmtime(gmtime(0));
  DUMP(offset);
#endif

  // Here we check the health of our RTC and in case we try to "fix it"
  // Common causes for it being invalid are:
  //    1) first time you ran and the device wasn't running yet
  //    2) the battery on the device is low or even missing


  // Check if the time is valid.
#ifndef DEBUG
  if (!Rtc.IsDateTimeValid())
#endif
  {
#ifndef DEBUG
    Serial.println(F("WARNING: RTC invalid time, setting RTC with compile time!"));
#else
    Serial.println(F("DEBUG mode: setting RTC with compile time!"));
#endif
    Rtc.SetTime(&compiled_time_tm);
  }

  // Check if the RTC clock is running (Yes, it can be stopped, if you wish!)
  if (!Rtc.GetIsRunning())
  {
    Serial.println(F("WARNING: RTC was not actively running, starting it now."));
    Rtc.SetIsRunning(true);
  }

  // We finally get the time from the RTC into a time_t value (let's call it "now"!)
  time_t now = Rtc.GetTime();
  #ifdef DEBUG
    DUMP(now);
  #endif

  // As stated above, we reset it to the "Compile time" in case it is "older"
  if (now < compiled_time_t)
  {
    Serial.println(F("WARNING: RTC is older than compile time, setting RTC with compile time!"));
    Rtc.SetTime(&compiled_time_tm);
  }

  #ifdef DS3231
  // Reset the DS3231 RTC status in case it was wrongly configured
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
  #endif

  #ifdef DEBUG
    Serial.println(F("Setup done."));
  #endif

  Serial.println("");
// End of Setup
}



// Main loop
void loop() {
  #ifdef DEBUG
    loops++;
  #endif

  // Here we check our RTC every "interval" milliseconds
  // We don't use delay() as we want our loop freerunning
  // in case we have other things to do beside reading the time/temperature...
  unsigned long current_millis = millis();
  unsigned long elapsed_millis = current_millis - prev_millis;
  if (elapsed_millis >= interval)
  {
    prev_millis = prev_millis + interval;

    #ifdef DEBUG
      DUMP(loops);
      loops = 0;
    #endif

    // HERE we read the RTC! It was the time, wasn't it?? ;-)
    if (Rtc.IsDateTimeValid())      // Check if the RTC is still reliable...
    {
                                    // Rtc.GetTime() returns the "time_t" time value:
                                    // this is universal, absolute, UTC based, arithmetic time,
      time_t now = Rtc.GetTime();   // counted as seconds since Jan 1, 2000 00:00:00.
                                    // Unhappily the time.h libray does not takes into account "leap seconds"
                                    // (See: https://en.wikipedia.org/wiki/Leap_second)

      // We can build and print a standard ISO timestamp with our *local* time
      struct tm local_tm;
      localtime_r(&now, &local_tm);  // localtime_r() convert the (universal, UTC based) arithmetic system time to a "struct tm" object with local time
      char local_timestamp[20];
      strcpy(local_timestamp, isotime(&local_tm));  // We use the standard isotime() function to build the ISO timestamp
      Serial.print(F("Local timestamp: "));
      Serial.print(local_timestamp);

      // ... same thing but with UTC time
      struct tm utc_tm;
      gmtime_r(&now, &utc_tm);       // but using the gmtime_r() function to convert the arithmetic system time to a "struct tm" object
      char utc_timestamp[20];
      strcpy(utc_timestamp, isotime(&utc_tm));
      Serial.print(F(" - UTC timestamp: "));
      Serial.print(utc_timestamp);
      Serial.println("");

      // We can also use the ctime() and asctime() functions for formatting our time:
      Serial.print(F("Local time: "));
      Serial.print(ctime(&now));       // ctime() simply uses the time_t arithmetic time type and takes into account our Time Zone
      Serial.print(F(" - UTC time: "));
      Serial.print(asctime(&utc_tm));  // While asctime uses the "struct tm" object and *does not* takes into account our Time Zone
      Serial.println("");

      // If we have a DS3231 we can read the temperature too...
      #ifdef DS3231
        float temperature = Rtc.GetTemperature();
        Serial.print(F("Temperature: "));
        Serial.print(temperature);
        Serial.print(F("C ("));
        Serial.print(temperature * 1.8 + 32);
        Serial.println(F("F)"));
      #endif

      Serial.println("");
    }
    else
    {
      // Battery on the device is low or even missing and the power line was disconnected
      Serial.println(F("RTC clock has failed!"));
    }
  }

// End of the loop
}
