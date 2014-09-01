#include "main.h"

void Swap(unsigned char*, unsigned char*);
void Encrypt(int);

void init(void)
{
	DDRC = 0xFF;
	PORTC = 0x00;

	tctr0_init();
	
	return;
}

int main(void)
{
	int keylength = 250;	
	
	init();
	
	while(1)
	{
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
		Encrypt(keylength);
	}

	return 0;
}


void Encrypt(int keylength)
{
	char *pt;
	pt = "this form is to be completed by persons who are able to comment on your qualifictions for graduate study. If you have been away from the academic institution for some time, hahaha rajesh here....!!!";


	int count = 0;
	unsigned char i, j, t, k, keylen;
	unsigned char  S[256], T[256];
	char c;
	keylen = (unsigned char)keylength;
	unsigned char K[keylen];
	i = 0;
	do{
		 K[i] = i; 
	}while(i++<(keylen-1));

	i = 0;
	do{	
		S[i] = i;
		T[i] = K[i %  keylen];
	}while(i++<255);

	i = 0;
	j = 0;
	do{
		j = (j + S[i] + T[i])%256;
		Swap((S+i), (S+j));
	}while(i++<255);

	i = 0;
	j = 0;
	c =  *(pt+0);
	while(count < 200)
	{
		i = (i+1)%256;
		j = (j+S[i])%256;
		Swap((S+i), (S+j));
		t = (S[i] + S[j]) % 256;
		k = S[t];
		c  = (char) (c ^ k);
		count++;
		c = *(pt+count);
	}
}

void Swap( unsigned char* a, unsigned char* b)
{
	unsigned char* t = a;
	a = b;
	b = t;
}
