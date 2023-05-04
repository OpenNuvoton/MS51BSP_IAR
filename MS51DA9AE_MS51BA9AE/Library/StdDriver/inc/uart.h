#define UART0_Timer1  0
#define UART0_Timer3  1
#define UART1_Timer3  2
#define UART0 0
#define UART1 1

extern   BIT PRINTFG,uart0_receive_flag,uart1_receive_flag;
extern   unsigned char uart0_receive_data,uart1_receive_data;

void UART_Open(unsigned long u32SysClock, unsigned char u8UARTPort,unsigned long u32Baudrate);
unsigned char Receive_Data(unsigned char UARTPort);
void UART_Send_Data(unsigned char UARTPort, unsigned char c);
void UART_Interrupt_Enable(unsigned char u8UARTPort, unsigned char u8UARTINTStatus);
void Enable_UART0_VCOM_printf_24M_115200(void);
void printf_UART(unsigned char *str, ...);