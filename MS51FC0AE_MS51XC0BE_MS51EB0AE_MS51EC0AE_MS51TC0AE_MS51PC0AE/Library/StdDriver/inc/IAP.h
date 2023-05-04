
void Trigger_IAP(void);
void Erase_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Erase_Verify_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Program_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Program_Verify_LDROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Erase_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Erase_Verify_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Program_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Program_Verify_APROM(unsigned int u16IAPStartAddress, unsigned int u16IAPDataSize);
void Modify_CONFIG(unsigned char u8CF0,unsigned char u8CF1,unsigned char u8CF2,unsigned char u8CF3,unsigned char u8CF4);
void Read_UID(void);
void Read_UCID(void);
void Read_DID(void);

extern unsigned char __xdata DIDBuffer[4];
extern unsigned char __xdata UIDBuffer[12];
extern unsigned char __xdata UCIDBuffer[12];
extern unsigned char __xdata IAPDataBuf[128];
extern unsigned char __xdata IAPCFBuf[5];