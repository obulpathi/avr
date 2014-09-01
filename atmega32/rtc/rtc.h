struct TIME
{
	uint8_t sec;
	uint8_t min;
	uint8_t hrs;

	uint8_t day;
	uint8_t month;
	uint16_t year;
};

typedef struct TIME time;
time rtc;

uint8_t month_days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

void rtc_init(void);
void rtc_set_time(time now);
void rtc_tick(void);
