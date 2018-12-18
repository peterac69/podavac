#include <avr/io.h>

int main(void) {
//Port B pins as input
DDRB=0x00;
//Enable internal pull ups
PORTB=0xFF;
//Set PORTD pin as output
DDRD=0xFF;
//Set PORTC pin as output
DDRC=0xFF;
//timer in WGM12 CTC mode - count to OCR1A value 
TCCR1B=0b00001000;
//Output compare OC1A and invert OC1B, COMA1=0 COMA0=1 COMB1=0 COMB0=1 VGM1=0 VGM0=0
TCCR1A=0b01010000;
//start timer without prescaler,
TCCR1B=0b00000001;
// initial OCR1A value count to 3FFF
OCR1A=0x3FFF;
for (;;)
   {
//loop output 185Hz pulse - osc 8 MHz
   }
}
