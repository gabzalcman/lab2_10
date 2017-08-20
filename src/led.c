#include <stdint.h>
#include <avr/io.h>
#include "led.h"


void led_init(void)
{
	
    TCCR0 |= (1<<WGM01)|(1<<WGM00)|(5<<CS00)|(1<<COM01)|(1<<COM00);
	DDRB |= _BV(PB3);
	OCR0 = 0;
}

void led_on(void)
{
    //PORTB |= _BV(PB3);
	OCR0 = 255;
}

void led_off(void)
{   
	//PORTB &= ~(_BV(PB3));
	OCR0 = 0;
}

void led_set_brightness(uint8_t value)
{
	// if (value)  led_on();
    // else        led_off();
	 if(value == 0){
		 
		 DDRB &= ~(_BV(PB3));
	 }else if((value > 0) & !(DDRB & (_BV(PB3)))){
	 DDRB |= _BV(PB3);
	 OCR0 = value;
	 }else{
		OCR0 = value; 
	 }
}

uint8_t led_get_brightness(void)
{
     // if (bit_is_set(PINB, PB3))  return 255;
    // else                        return 0;
	return OCR0;
   
}