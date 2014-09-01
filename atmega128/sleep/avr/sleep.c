void sleep()
{
	sleep_enable();
	sleep_cpu();
	sleep_disable();

	return;
}
