#define UART2_TXD   0
#define UART2_RXD   1


extern unsigned char uart2rvbuffer;
extern BIT uart2rvflag;


void UART2_Open(unsigned long u32SysClock, unsigned long u32Baudrate);
unsigned char UART2_Receive_Data();
void UART2_Send_Data(unsigned char c);
void UART2_Interrupt(unsigned char u8UART2INTSel,unsigned char u8UART2INTStatus);