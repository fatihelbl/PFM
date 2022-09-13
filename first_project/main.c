#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "language_support.h"
#define FLASH_ADDRESS 0x860

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

/*  void data_write(uint8_t bAdd, uint8_t bData)
{
    uint8_t GIEBitValue = INTCONbits.GIE;
    NVMADRU = 0x31;
    NVMADRH = 0x00;
    NVMADRL = (uint8_t)((bAdd) & 0xFF);
    NVMDATL = (uint8_t)((bData) & 0xFF);
    //bool is_write_done = 0;
    NVMCON0bits.NVMEN=1;
    INTCONbits.GIE=0;

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
*/
void main(void)
{
    SYSTEM_Initialize();

    TRISA6 = 0;
    uint8_t counter = 0;
    build_address(0x860);
    NOP();
    NOP();
    data_upload(string,6);
    NOP();
    NOP();
    data_write();
    //data_write(FLASH_ADDRESS,string);
    
    while (1)
    {
      LATA6 = 1;
      __delay_ms(500);
      printf("");
      LATA6 = 0;
      __delay_ms(500);
      
      counter++;
      
      if(counter == 3)
      {
          asm("goto 0x1000");
          counter = 0;
      }
    }
}