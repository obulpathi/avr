
// Utility to fix checksums in Intel hex file records.
// 12/23/04 - JLPost
//
//-----------------------------------------------------------------------------
//
//	This program is free software; you can redistribute it and/or
//	modify it under the terms of the GNU General Public License
//	as published by the Free Software Foundation; either version 2
//	of the License, or (at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//-----------------------------------------------------------------------------
//

#include	<stdio.h>
#include	<ctype.h>
#include	<string.h>

#define	byte		unsigned char
#define	BFRLEN	256

char	fname[256];
char	bfr[BFRLEN];

byte ascii2hex(char *str)
{
	byte	data, result;

	result = 0;
	data = (byte) toupper(*str);
	data -= 0x30;

	if (data > 9)
		data -= 7;

	result = data << 4;
	str++;
	data = (byte) toupper(*str);
	data -= 0x30;

	if (data > 9)
		data -= 7;

	result |= data;
	return result;
}

byte compute_checksum(char *str)
{
	byte	i, len, chksum;

	str++;						// skip over ':'
	len = ascii2hex(str);	// get number of bytes in record
	chksum = len;
	len +=3;						// add 3 for address and record type
	str += 2;

	for (i=0; i<len; i++)
	{
		chksum += ascii2hex(str);
		str += 2;
	}

	chksum ^= 0xff;
	chksum++;
	chksum &= 0xff;
	str += 2;
	*str = '\0';				// null terminate the line
	return chksum;
}

int main(int argc, char *argv[])
{
	int	i, line, fixed;
	byte	cksum, fcksum;
	FILE	*fp, *fpout;

	if (argc < 2)
	{
		printf("\nUsage: %s <filename>\n\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("\nCan't open input file %s\n\n", argv[1]);
		return 1;
	}

	strcpy(fname, argv[1]);
	i = strlen(fname) - 4;

	if (!strcasecmp((char *) &fname[i], ".hex"))
		fname[i] = '\0';

	strcat(fname, "-fixed.hex");

	fpout = fopen(fname, "w");

	if (fpout == NULL)
	{
		fclose(fp);
		printf("\nCan't open output file!\n\n");
		return 1;
	}

	printf("\n");
	line = fixed = 0;

	while (!feof(fp))
	{
		if (!fgets(bfr, BFRLEN - 1, fp))
			break;

		line++;
		cksum = compute_checksum(bfr);
		i = strlen(bfr);
		i -= 2;
		fcksum = ascii2hex((char *) &bfr[i]);

		if (cksum != fcksum)									// if checksums don't match,
		{
			printf("setting checksum to %02X in line %d: %s\n",
				cksum, line, bfr);
			sprintf((char *) &bfr[i], "%02X", cksum);	// fix the record
			fixed++;
		}

		fprintf(fpout, "%s\n", bfr);
	}

	printf("%d lines processed, %d lines modified\n\n", line, fixed);
	fclose(fp);
	fflush(fpout);
	fclose(fpout);

	if (!fixed)			// if nothing modified, remove output file
		remove(fname);

	return 0;
}

// end
