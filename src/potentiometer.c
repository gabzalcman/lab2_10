#include <stdint.h>
#include <avr/io.h>
#include "potentiometer.h"

void pot_init(void)
{
    // TODO: Configure ADC
	ADCSRA |= (1<<ADEN)|(6<<ADPS0);
	ADMUX = 0;
	ADMUX|= (1<<REFS0);

}

uint16_t pot_get_value(void)
{
    // TODO: Do a single ADC conversion and return 10-bit result
uint16_t ADC_temp;
		
	ADCSRA |= 1<<ADSC; // Start conversion
	while(!(ADCSRA & (1<<ADIF))); // Wait for conversion
	ADC_temp = ADCL; // Read low byte first
	ADC_temp |= ADCH<<8; // Read high byte last
	
    return ADC_temp;
}