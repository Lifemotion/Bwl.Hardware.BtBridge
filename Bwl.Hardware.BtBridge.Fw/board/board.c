#include "board.h"

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

float battery_voltage()
{
	adc_init(ADC_MUX_ADC7, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_2_56, ADC_PRESCALER_128);
	return 7.8*2.56/1024*adc_read_average(5);
}

void board_init()
{
	hc_configure();
	uart_init_withdivider(1, 207);
	pin_input_pullup(BUTTON_1);
	pin_low(IR_POWER_PIN);
	pin_input_pullup(BUTTON_2);
	pin_low(LED_1);
	var_delay_ms(2000);
	pin_high(LED_1);
}