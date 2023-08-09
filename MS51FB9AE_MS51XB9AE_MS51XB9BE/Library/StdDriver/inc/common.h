#define  GPIO_LED     P12
#define  GPIO_LED_QUASI_MODE     P12_QUASI_MODE
#define  GPIO_PRINTF  P06

extern BIT BIT_TMP;

unsigned char Read_APROM_BYTE(unsigned int __code *u16_addr);
void _delay_(void);