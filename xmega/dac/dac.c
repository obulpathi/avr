void DAC_DualChannel_Enable(void)
{
	DACB.CTRLB = DACB.CTRLB | DAC_CHSEL_DUAL_gc;
	DACB.CTRLC = DAC_REFSEL_AVCC_gc;
	DACB.TIMCTRL = (uint8_t) DAC_CONINTVAL_4CLK_gc | DAC_REFRESH_32CLK_gc;
	DACB.CTRLA = DACB.CTRLA | DAC_CH1EN_bm | DAC_CH0EN_bm | DAC_ENABLE_bm;

	return;
}

int DAC_Channel0_Ready()
{
	return ~DACB.STATUS & DAC_CH0DRE_bm;
}

int DAC_Channel1_Ready()
{
	return ~DACB.STATUS & DAC_CH1DRE_bm;
}

void DAC_Channel0_Write(int data)
{
	DACB.CH0DATA = data;

	return;
}

void DAC_Channel1_Write(int data)
{
	DACB.CH1DATA = data;

	return;
}
