#include "PWM.h"

#define PWM_PERIOD	256
#define PWM_OFF		PORTB &= ~(1<<PORTB5)
#define PWM_ON		PORTB |= (1<<PORTB5)
#define PWM_START	DDRB |= (1<<PORTB5)

static uint8_t PWM_DELTA;

void PWM_soft_Update(void){
	static uint16_t PWM_position = 0;
	if (++PWM_position >= PWM_PERIOD){
		PWM_position = 0;
		PWM_OFF;
	}
	else{
		if (PWM_position < PWM_DELTA){
			PWM_OFF;
		}
		else{
			PWM_ON;
		}
	}
}

void PWM_soft_init(){
	PWM_START;
	PWM_OFF;
	PWM_DELTA = 1;
}

uint8_t PWM_get_comp_value(){
	return PWM_DELTA;
}

void PWM_set_comp_value(uint8_t value){
	PWM_DELTA = value;
}