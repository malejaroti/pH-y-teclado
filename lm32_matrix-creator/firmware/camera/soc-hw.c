#include "soc-hw.h"


uart_t       *uart0       = (uart_t *)       0x20000000;
timerH_t     *timer0      = (timerH_t *)     0x30000000;
camera_t     *camera0     = (camera_t *)     0x40000000;
//keypad_t     *keypad0     = (keypad_t *)     0x50000000;
//SK6812RGBW_t *SK6812RGBW0 = (SK6812RGBW_t *) 0x60000000;

isr_ptr_t isr_table[32];

/***************************************************************************
 * IRQ handling
 */


uint32_t count;


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

void isr_null(void)
{
}

void irq_handler(uint32_t pending)
{     
    uint32_t i;
    for(i=0; i<32; i++) {
        if (pending & 0x00000001){
            (*isr_table[i])();
        }
        pending >>= 1;
    }
}

void isr_init(void)
{
    int i;
    for(i=0; i<32; i++)
        isr_table[i] = &isr_null;
}

void isr_register(int irq, isr_ptr_t isr)
{
    isr_table[irq] = isr;
}

void isr_unregister(int irq)
{
    isr_table[irq] = &isr_null;
}

/***************************************************************************
 * TIMER Functions
 */
uint32_t tic_msec;

void mSleep(uint32_t msec)
{
    uint32_t tcr;

    // Use timer0.1
    timer0->compare1 = (FCPU/1000)*msec;
    timer0->counter1 = 0;
    timer0->tcr1 = TIMER_EN;

    do {
        //halt();
         tcr = timer0->tcr1;
     } while ( ! (tcr & TIMER_TRIG) );
}

void uSleep(uint32_t usec)
{
    uint32_t tcr;

    // Use timer0.1
    timer0->compare1 = (FCPU/1000000)*usec;
    timer0->counter1 = 0;
    timer0->tcr1 = TIMER_EN;

    do {
        //halt();
         tcr = timer0->tcr1;
     } while ( ! (tcr & TIMER_TRIG) );
}

void tic_isr(void)
{
    tic_msec++;
    timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

//	uart_putchar(count+48);
    
//    uart_putchar(tic_msec+40);

}

void tic_init(void)//registro de la interrupcion /reset and start timer
{
    tic_msec = 0;

    // Setup timer0.0
    timer0->compare0 = (FCPU);
    timer0->counter0 = 0;
    timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

    isr_register(1, &tic_isr);
}


/***************************************************************************
 * UART Functions
 */
void uart_init(void)
{
    //uart0->ier = 0x00;  // Interrupt Enable Register
    //uart0->lcr = 0x03;  // Line Control Register:    8N1
    //uart0->mcr = 0x00;  // Modem Control Register

    // Setup Divisor register (Fclk / Baud)
    //uart0->div = (FCPU/(57600*16));
}

char uart_getchar(void)
{   
    while (! (uart0->ucr & UART_DR)) ;
    return uart0->rxtx;
}

void uart_putchar(char c)
{
    while (uart0->ucr & UART_BUSY) ;
    uart0->rxtx = c;
}

void uart_putstr(char *str)
{
    char *c = str;
    while(*c) {
        uart_putchar(*c);
        c++;
    }
}



//Camera

uint32_t camera_data(void)
{
	return (camera0->dataOut);
}


uint32_t camera_finish(void)
{
	return camera0->ready;
}

int i;

void camera_init(void){
	//if (camera_finish()){	
		for (i=0;i<320*240;i++){			
			camera0->add_rd =i;
			uart_putchar(camera0->dataOut);
			uart_putstr("Hi \n");
		}
	//}
}
