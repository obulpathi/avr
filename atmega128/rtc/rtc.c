void rtc_init(void)
{
	rtc.sec = 0;
	rtc.min = 0;
	rtc.hrs = 0;

	rtc.day = 1;
	rtc.month = 1;
	rtc.year = 2000;

	// init the timer and stuff ... 

	return;
}

void rtc_set_time(time now)
{
	// disable interrupts
	cli();

	rtc.sec = now.sec;
	rtc.min = now.min;
	rtc.hrs = now.hrs;

	rtc.day = now.day;
	rtc.month = now.month;
	rtc.year = now.year;

	// reenable interrupts
	sei();

	return;
}

// timer ticks ... 
void rtc_tick(void)
{
	rtc.sec++;

	if( rtc.sec == 60 )
	{
		rtc.sec = 0;
		rtc.min++;

		if( rtc.min == 0 )
		{
			rtc.min = 0;
			rtc.hrs++;

			if( rtc.hrs == 24 )
			{
				rtc.hrs = 0;
				rtc.day++;

				// if leap day
				if( ( rtc.day == 29 ) && ( rtc.month == 2 ) && ( rtc.year % 4 == 0 ) )
						return;

				if( rtc.day > month_days[rtc.month] )
				{
					rtc.day = 1;
					rtc.month++;

					if( rtc.month == 13 )
					{
						rtc.month = 1;
						rtc.year++;
					}
				}
			}
		}
	}

	return;
}
