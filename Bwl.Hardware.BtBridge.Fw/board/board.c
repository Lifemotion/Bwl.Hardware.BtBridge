#include "board.h"

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++){_delay_ms(1.0);wdt_reset();}
}

float battery_voltage()
{
	adc_init(ADC_MUX_ADC7, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_2_56, ADC_PRESCALER_128);
	return 7.8*2.56/1024*adc_read_average(5);
}

void hc_uart_send(char data)
{
	uart_send(0, data);
}
unsigned char hc_uart_get()
{
	return uart_get(0);
}

unsigned char hc_uart_received()
{
	return uart_received(0);
}

void hc_key_pin_set(char isHigh)
{
	if(isHigh){
		pin_high(HC_KEY);
	}else{
		pin_low(HC_KEY);		
	}
}


void board_init()
{
	//uart_init_withdivider(0, GET_UBRR(F_CPU,38400));
	//hc_init("OrlanTool","0000");
	uart_init_withdivider(0, GET_UBRR(F_CPU,9600));
	pin_input_pullup(BUTTON_1);
	pin_input_pullup(BUTTON_2);
	pin_input_pullup(BUTTON_MODE);
	pin_low(IR_POWER_PIN);
	pin_low(LED_1);
	pin_high(LED_1);
}