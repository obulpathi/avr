#define	XAXIS	0x01
#define YAXIS	0x02
#define ZAXIS	0x03

void micromag3_init(void);
int micromag3_read(unsigned char axis);
