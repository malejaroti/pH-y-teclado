
/*- Includes ---------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soc-hw.h"

/*- Definitions ------------------------------------------------------------*/
#ifndef UART_COMMANDS_BUFFER_SIZE
#define UART_COMMANDS_BUFFER_SIZE  100
#endif

#define FINALCHARACTER1 '\r'
#define FINALCHARACTER2 '\n'

/*- Variables --------------------------------------------------------------*/
char UartBuffer[UART_COMMANDS_BUFFER_SIZE];
uint32_t UartBufferPtr = 0;



char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}



int main(void){
    
    // Init Commands
    irq_set_mask( 0x00000012 );
    isr_init();
   // keypad_init();
    camera_init();
    tic_init();
    irq_enable();
    uart_init();
    mSleep(100);
    char b[50];
//    SK6812RGBW_rgbw(0x0000ff00);
    while (1){
	uint32_t nelson=camera_data();
	uart_putstr(itoa(nelson, b));
	mSleep(1000);
	
    } 
    return 0;
}
