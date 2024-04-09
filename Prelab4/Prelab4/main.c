#define F_CPU 16000000
//LIBRERIAS
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

uint8_t counter = 0;

//INICIO VA.
void initADC(void);

int main(void)
{
	cli();
	DDRC |= (1 << PINC1) | (1 << PINC2) | (1 << PINC3); //TRANSISTORES
	PORTC = 0;
	PORTC |= (1 << PORTC1);
	
	//LIEMPIAR PUERTOD
	DDRD = 0xFF;
	PORTD = 0;
	UCSR0B = 0;
	
	//ASIGNACIONES
	PORTB |= (1 << PINB0) | (1 << PINB1); //SALIDAS
	DDRB &= ~(1 << PINB0) | ~(1 << PINB1); //ENTRADAS
	
	
	
	initADC();
	sei();

	//loop
	while (1)
	{
		PORTD = counter;
	}
}

void initADC(void){
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT0) | (1 << PCINT1);
}

//operation
ISR (PCINT0_vect){
	if (!(PINB & (1 << PINB0))) {
		counter++;
		}else if (!(PINB & (1 << PINB1))) {
		counter--;
		}else{
		counter = counter;
	}
}
