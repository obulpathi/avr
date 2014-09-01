int sleep_init(void)
{
	set_sleep_mode(SLEEP_MODE_ADC);	// select sleep mode

	return 0;
}

void sleep(void)
{
	sleep_enable();				// enables sleep
	sleep_mode();				// sleeps the device
	sleep_disable();			// dislables sleep

	return;
}
