#include <time.h>

uint8_t BcdToUint8(uint8_t val)
{
    return val - 6 * (val >> 4);
}


uint8_t Uint8ToBcd(uint8_t val)
{
    return val + 6 * (val / 10);
}


uint8_t BcdHourToUint8(uint8_t bcdHour)
{
    uint8_t hour;
    if (bcdHour & 0x40)
    {
        // 12 hour mode, convert to 24
        bool isPm = ((bcdHour & 0x20) != 0);

        hour = BcdToUint8(bcdHour & 0x1f);
        if (isPm)
        {
           hour += 12;
        }
    }
    else
    {
        hour = BcdToUint8(bcdHour);
    }
    return hour;
}


int StringToInt(const char* pString)
{
    int value = 0;

    // skip leading 0 and spaces
    while ('0' == *pString || *pString == ' ')
    {
        pString++;
    }

    // calculate number until we hit non-numeral char
    while ('0' <= *pString && *pString <= '9')
    {
        value *= 10;
        value += *pString - '0';
        pString++;
    }
    return value;
}


extern time_t CompileTime (const char* date, const char* time)
{
  struct tm tm_time;

  // Get the month  (N.B.: Jan=0, Feb=1, etc...)
  switch (date[0])
  {
  case 'J':
    if ( date[1] == 'a' )
	    tm_time.tm_mon = 0;
	  else if ( date[2] == 'n' )
	    tm_time.tm_mon = 5;
	  else
	    tm_time.tm_mon = 6;
    break;
  case 'F':
    tm_time.tm_mon = 1;
    break;
  case 'A':
    tm_time.tm_mon = date[1] == 'p' ? 3 : 7;
    break;
  case 'M':
    tm_time.tm_mon = date[2] == 'r' ? 2 : 4;
    break;
  case 'S':
    tm_time.tm_mon = 8;
    break;
  case 'O':
    tm_time.tm_mon = 9;
    break;
  case 'N':
    tm_time.tm_mon = 10;
    break;
  case 'D':
    tm_time.tm_mon = 11;
    break;
  }

  // Get the day
  tm_time.tm_mday = (int8_t) StringToInt(date + 4);

  // Get the year
  int16_t year =  (int16_t) StringToInt(date + 7);
  tm_time.tm_year = year - 1900;

  // Get the time
  tm_time.tm_hour = (int8_t) StringToInt(time);
  tm_time.tm_min  = (int8_t) StringToInt(time + 3);
  tm_time.tm_sec  = (int8_t) StringToInt(time + 6);
  tm_time.tm_wday = 0;
  tm_time.tm_isdst = 0;

  return mktime(&tm_time);
}
