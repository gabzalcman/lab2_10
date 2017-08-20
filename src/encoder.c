#include <stdint.h>
#include <avr/io.h>
#include "encoder.h"

static int32_t _count = 0;
//DDRD |= ~((1<<PD2) | (1<<PD3));

// Forward decl of private helper functions
static void _encoder_enable_interrupts(void);
static void _encoder_disable_interrupts(void);

void encoder_init(void)
{
    // TODO: Enable pullup resistors (if not done in hardware)

    // TODO: Configure interrupt edge triggers for INT0 and INT1
	MCUCR |= (1<<ISC10)|(1<<ISC00);

    // Set default count
    _count = 0;

    // Enable interrupts INT0 and INT1
    _encoder_enable_interrupts();
}

void encoder_edge_A_isr(void)
{
    // TODO: Implement A edge logic to increment or decrement _count
	if(!!(PIND & (1<<PD2)) == !!(PIND & (1<<PD3))){
		_count++;
	}else{
		_count--;
	}
}

void encoder_edge_B_isr(void)
{
    // TODO: Implement B edge logic to increment or decrement _count
	if(!!(PIND & (1<<PD2)) == !!(PIND & (1<<PD3))){
		_count--;
	}else{
		_count++;
	}
}

void encoder_set_count(int32_t count)
{
    // Atomically set _count
    _encoder_disable_interrupts();
    _count = count;
    _encoder_enable_interrupts();
}

int32_t encoder_get_count(void)
{
    // Atomically read _count
    _encoder_disable_interrupts();
    uint32_t count = _count;
    _encoder_enable_interrupts();
    return count;
}

int32_t encoder_pop_count(void)
{
    // Atomically read and reset _count
    _encoder_disable_interrupts();
    int32_t count = _count;
    _count = 0;
    _encoder_enable_interrupts();
    return count;
}

void _encoder_enable_interrupts(void)
{
    // TODO: Enable INT0 and INT1 interrupts
	GICR |= (3<<INT0);
}

void _encoder_disable_interrupts(void)
{
    // TODO: Disable INT0 and INT1 interrupts
	GICR &= ~(3<<INT0);
}

