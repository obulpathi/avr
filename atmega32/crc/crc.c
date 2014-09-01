uint8_t crc(uint8_t *data, uint8_t length)
{
	uint8_t crc, i;

	for( i = 0 ; i < length ; i++ )
		crc = _crc_ibutton_update( crc, data[i] );

    return crc;
}
