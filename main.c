#include "h.h"
//#include <p24hj128gp202.h>

unsigned short bin2bcd(unsigned short binary_value)
{
  unsigned short temp;
  unsigned short retval;

  temp = binary_value;
  retval = 0;

  while(1)
  {

    if(temp >= 10)
    {
      temp -= 10;
      retval += 0x10;
    }
    else
    {
      retval += temp;
      break;
    }
  }

  return(retval);
}


unsigned short bcd2bin(unsigned short bcd_value)// Input range - 00 to 99.
{
  unsigned short temp;

  temp = bcd_value;
  temp >>= 1;

  temp &= 0x78;

  return(temp + (temp >> 2) + (bcd_value & 0x0f));
}

void setRTCTime(unsigned char year, unsigned char month, unsigned char day, unsigned char weekday, unsigned char hour, unsigned char minute, unsigned char second)
{

	NVMKEY = 0x55;
	NVMKEY = 0xAA;
	RCFGCALbits.RTCWREN = 1;

	RCFGCALbits.RTCEN = 0;

	RCFGCALbits.RTCPTR = 3;
	RTCVAL = bin2bcd(year); 					// Set Year
	RTCVAL = (bin2bcd(month) << 8) + bin2bcd(day);// Set Month and Day
	RTCVAL = (bin2bcd(weekday) << 8) + bin2bcd(hour); 	// Set Weekday and Hour (#0x0WHH).
	RTCVAL = (bin2bcd(minute) << 8) + bin2bcd(second);  // Set Minute and Second (#0xMMSS)

	RCFGCALbits.RTCEN = 1;

	RCFGCALbits.RTCWREN = 0;
}

RTCTime getRTCTime()
{
	RTCTime retVal;


	while(RCFGCALbits.RTCSYNC == 1);

	RCFGCALbits.RTCPT = 3;

	retVal.year = bcd2bin(RTCVAL);

	unsigned int month_date = RTCVAL;
	retVal.month = bcd2bin(month_date >> 8);
	retVal.day = bcd2bin(month_date & 0xFF);

	unsigned int wday_hour = RTCVAL;
	retVal.weekday = bcd2bin(wday_hour >> 8);
	retVal.hour = bcd2bin(wday_hour & 0xFF);

	unsigned int min_sec = RTCVAL;
	retVal.minute = bcd2bin(min_sec >> 8);
	retVal.second = bcd2bin(min_sec & 0xFF);

	return retVal;
}
