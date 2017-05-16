
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

/*
char key11[]={'a','b','c','1','A','B','C'};
char key21[]={'d','e','f','2','D','E','F'};
char key31[]={'g','h','i','3','G','H','I'};
char key41[]={'j','k','l','4','J','K','L'};
char key51[]={'m','n','o','5','M','N','O'};
char key61[]={'p','q','r','6','P','Q','R'};
char key71[]={'s','t','u','7','S','T','U'};
char key81[]={'v','w','x','8','V','W','X'};
char key91[]={'y','z','p','9','Y','Z','P'};


int i1;
int i2;
int i3;
int i4;
int i5;
int i6;
int i7;
int i8;
int i9;
*/


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
    keypad_init();
    tic_init();
    irq_enable();
    uart_init();
    mSleep(100);
//    SK6812RGBW_rgbw(0x0000ff00);
 
    return 0;
}
