void sleep(void)
{
	set_sleep_mode(SLEEP_MODE_IDLE);	// select sleep mode
	sleep_enable();				// enables sleep
	sleep_mode();				// sleeps the device
	sleep_disable();			// dislables sleep

	return;
}
