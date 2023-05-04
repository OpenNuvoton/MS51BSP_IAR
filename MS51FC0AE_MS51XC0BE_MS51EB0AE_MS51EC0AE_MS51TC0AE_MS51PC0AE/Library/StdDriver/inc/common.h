

extern BIT BIT_TMP;

extern unsigned char __data TA_REG_TMP,BYTE_TMP,SFRS_TMP;

unsigned char Read_APROM_BYTE(unsigned int __code *u16_addr);
void _delay_(void);
void SW_Reset(void);