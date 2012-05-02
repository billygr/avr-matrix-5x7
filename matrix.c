#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "matrix.h"
#include "font5x7.h"

extern unsigned char font5x7 [];

volatile unsigned int display;

ISR (SIG_OVERFLOW2)
{
/*
        Timer2 overflows every 16.384mS
        We read the font from the font table and update the ROW value accordinly
*/

        /* TODO: pgm_read_byte is cpu intensive, optimize the code   */
        ROWS=pgm_read_byte(&(font5x7[display]));;cbi(COLUMNS,COL1);_delay_ms(3);sbi(COLUMNS,COL1);
        ROWS=pgm_read_byte(&(font5x7[display+1]));;cbi(COLUMNS,COL2);_delay_ms(3);sbi(COLUMNS,COL2);
        ROWS=pgm_read_byte(&(font5x7[display+2]));;cbi(COLUMNS,COL3);_delay_ms(3);sbi(COLUMNS,COL3);
        ROWS=pgm_read_byte(&(font5x7[display+3]));;cbi(COLUMNS,COL4);_delay_ms(3);sbi(COLUMNS,COL4);
        ROWS=pgm_read_byte(&(font5x7[display+4]));;cbi(COLUMNS,COL5);_delay_ms(3);sbi(COLUMNS,COL5);
}

int main( void )
{
        unsigned int loc=0;

        /* Make all pins of port D/C as output  */
        DDRD = 0xFF;
        DDRC = 0xFF;

        COLUMNS=0xFF;
        ROWS=0;

        /* Use Timer2 for updating the display via the Timer2 overflow interrupt        */
        TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20); //Set prescalar to clk/1024 : 1 click = 64us (assume 16MHz)
        TIMSK2 = (1<<TOIE2);
        //TCNT2 should overflow every 16.384 ms (256 * 64us)

        /* Enable Interrupts     */
        sei();

        /* Go over the font table and display it        */
        for (loc=5;loc<=475;loc=loc+5)
        {
                display=loc;_delay_ms(50);
        }

        /* Disable Interupts    */
        cli();

        /* Shutdown the displays     */
        COLUMNS=0xFF;
        ROWS=0;

        while (1) { }
}
