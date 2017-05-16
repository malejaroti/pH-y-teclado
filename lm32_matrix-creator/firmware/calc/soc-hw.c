#include "soc-hw.h"


uart_t       *uart0       = (uart_t *)       0x20000000;
timerH_t     *timer0      = (timerH_t *)     0x30000000;
gpio_t       *gpio0       = (gpio_t *)       0x40000000;
keypad_t     *keypad0     = (keypad_t *)     0x50000000;
//SK6812RGBW_t *SK6812RGBW0 = (SK6812RGBW_t *) 0x60000000;

isr_ptr_t isr_table[32];

/***************************************************************************
 * IRQ handling
 */


uint32_t count;
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

/***************************************************************************
 * keypad Functions
 */
/*variables inicio edicion*/
volatile char key_old;
volatile char key_new;

char key1[]={'a','b','c','1','A','B','C',33,34,62};
char key2[]={'d','e','f','2','D','E','F',35,36,63};
char key3[]={'g','h','i','3','G','H','I',37,38,64};
char key4[]={'j','k','l','4','J','K','L',39,40,91};
char key5[]={'m','n','o','5','M','N','O',41,42,92};
char key6[]={'p','q','r','6','P','Q','R',43,44,93};
char key7[]={'s','t','u','7','S','T','U',45,46,94};
char key8[]={'v','w','x','8','V','W','X',47,58,95};
char key9[]={'y','z',169,'9','Y','Z',229,59,60,96};
char key0[]={'0',61,123,124,125,126,252,253,254,255};

/*variables final edicion*/

char keypad_read_data(void)
{
	return keypad0->keypad_data;
}

void keypad_init(void)//registro de la interrupcion
{
    isr_register(4, &keypad_isr); //funcion que se ejecuta con la interrupcion
}

void reset_and_start_timer(void){
	tic_msec=0;
}
/* inicio edicion */


char keypad_dec(void){
//here1:
//	reset_and_start_timer();
	if (tic_msec>3){	
		key_new=keypad_read_data()+48;
		reset_and_start_timer();
		count=0;
		key_old=key_new;
	}else{
			key_new=keypad_read_data()+48;
			if (key_new==key_old){
				count=count+1;
				if (count ==10) count=0;
				reset_and_start_timer();
				key_old=key_new;
				uart_putchar('\b');
			} else {
				reset_and_start_timer();
				key_old=key_new;
				count=0;
			}
		}
return put_char(key_new, count);
}


char put_char(char num, uint32_t count1){
	#if debug
		uart_putchar(num);
	#endif
	uint8_t tmp;
        switch (num){
		case 0x30:
		tmp= key0[count1];
		break;	
		case 0x31:
		tmp= key1[count1];
		break; 
		case 0x32:	
		tmp= key2[count1];
		break;	
		case 0x33:
		tmp= key3[count1];
		break;	
		case 0x34:
		tmp= key4[count1];
		break;	
		case 0x35:
		tmp= key5[count1];
		break;	
		case 0x36:	
		tmp= key6[count1];
		break;	
		case 0x37:
		tmp= key7[count1];
		break;	
		case 0x38:
		tmp= key8[count1];
		break;	
		case 0x39:
		tmp= key9[count1];
		break;	
		default:
		tmp= '0';
		break;
	}

	#if debug
//		uart_putchar(tmp);
	#endif
	return tmp;
}

/* fin edicion */


void keypad_isr(void){
	uart_putchar(keypad_dec());
}



