#include "mcc_generated_files/mcc.h"
uint8_t string[6]="Fatihh";
void build_address(uint32_t address)
{
    TBLPTRU = (address & 0xFF0000 ) >>16;
    TBLPTRH = (address & 0xFF00) >> 8;
    TBLPTRL = (address & 0xFF);
}
void data_upload(uint8_t* pData,uint8_t nLen)
{
    uint8_t i=0x00;
    for(i=0x00;i<nLen;i++)
 {
    TABLAT =pData[i];
    asm("TBLWT*+");
 }
}
void data_write(void)
{
    //bool is_write_done = 0;
    uint8_t GIEBitValue = INTCONbits.GIE;
    INTCONbits.GIE=0;
    NVMCON0bits.NVMEN=1;
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR=1;
    while (NVMCON1bits.WR)
        ;

    INTCONbits.GIE = GIEBitValue;
    NVMCON0bits.NVMEN = 0;

    //is_write_done = 1;

    //return (is_write_done);
    
}
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    TRISA7 = 0;
    uint8_t counter = 0;
    build_address(0x1080);
    NOP();
    NOP();
    data_upload(string,6);
    NOP();
    NOP();
    data_write();
    NOP();
    NOP();
    while (1)
    {
        LATA7 = 1;
        __delay_ms(1000);
        printf("I'm Here");
        LATA7 = 0;
        __delay_ms(100);
        
        counter++;
        
        
        if(counter == 3)
        {
          asm("goto 0x500");
          counter = 0;
        }
    }
}
