#ifndef H_H_INCLUDED
#define H_H_INCLUDED


typedef struct _RTCTime
{
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char weekday;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
} RTCTime;

void setRTCTime(unsigned char year, unsigned char month, unsigned char day, unsigned char weekday, unsigned char hour, unsigned char minute, unsigned char second);
RTCTime getRTCTime();



#endif
