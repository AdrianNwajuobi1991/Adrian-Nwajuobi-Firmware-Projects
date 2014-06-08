#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

uint16_t readADC (uint8_t channel){
	ADMUX = (0xf0 & ADMUX) | channel;
	ADCSRA |= (1 << ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	return (ADC);
}
int main (void){
	uint16_t lightThreshold;
	uint16_t sensorValue;
	//ADC Setup
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN);
	//ADC Setup complete
	DDRB = 0xff;
	while (1) {
		lightThreshold = readADC(PC3);
		sensorValue = readADC(PC0);
		if(sensorValue < lightThreshold){
			PORTB = 0xff;
		}else{
			PORTB = 0x00;
		}
	}
	return(0);
}

