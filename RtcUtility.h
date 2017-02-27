#ifndef __RTCUTILITY_H__
#define __RTCUTILITY_H__
#include <time.h>

extern uint8_t BcdToUint8(uint8_t val);
extern uint8_t Uint8ToBcd(uint8_t val);
extern uint8_t BcdHourToUint8(uint8_t bcdHour);
extern int StringToInt(char* pString);
extern time_t CompileTime (const char* date, const char* time);

#endif // __RTCUTILITY_H__
