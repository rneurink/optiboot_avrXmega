/*
 * Blinky.cpp
 *
 * Created: 08/05/2021 14:52:02
 * Author : Ruben
 */ 

#define F_CPU 20000000

#include <avr/io.h>
#include <avr/xmega.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	sei();
	_PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, 0x10);
    PORTC.PIN5CTRL = 0x0B; // Enable pullup and falling interrupt
    PORTB.DIRSET |= 1 << 4;
    
    while (1) {
	    PORTB.OUTTGL |= 1 << 4;
	    _delay_ms(500);
    }
    
    return 0;
}

ISR(PORTC_PORT_vect)
{
	// Call the interrupt handler for the callback registered at runtime
	if(VPORTC.INTFLAGS & PORT_INT5_bm)
	{
		_PROTECTED_WRITE(RSTCTRL.SWRR, 0x1);
	}

	/* Clear interrupt flags */
	VPORTC.INTFLAGS = 0xff;
}