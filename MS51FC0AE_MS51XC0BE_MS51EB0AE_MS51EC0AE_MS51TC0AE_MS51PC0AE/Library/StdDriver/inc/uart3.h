#define UART3_TXD   0
#define UART3_RXD   1


extern unsigned char uart3rvbuffer;
extern BIT  uart3rvflag;

void UART3_Open(unsigned long u32SysClock, unsigned long u32Baudrate);
unsigned char UART3_Receive_Data();
void UART3_Send_Data(unsigned char c);
void UART3_Interrupt(unsigned char u8UART3INTSel,unsigned char u8UART3INTStatus);