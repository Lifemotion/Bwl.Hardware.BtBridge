#include "board/board.h"

unsigned char mode = 0;

void select_mode()
{	
	if(pin_get_in(BUTTON_1)==0 || pin_get_in(BUTTON_2)==0)var_delay_ms(300);
	if(pin_get_in(BUTTON_1)==0 && pin_get_in(BUTTON_2)==0){
		//UART mode
		mode = 1;
		uart_init_withdivider(1, 12);
		pin_low(RS_TXEN);
		pin_high(RS_RXEN);
		pin_low(LED_3);
		pin_high(IR_POWER_PIN);
		var_delay_ms(2000);
		pin_high(LED_3);
	}else if(pin_get_in(BUTTON_1)==0){
		mode = 0;
		uart_init_withdivider(1, 207);
		pin_low(IR_POWER_PIN);
		pin_high(RS_TXEN);
		pin_low(RS_RXEN);
		pin_low(LED_1);
		var_delay_ms(2000);
		pin_high(LED_1);

	}else if(pin_get_in(BUTTON_2)==0){
		//RS485 mode
		uart_init_withdivider(1, 12);
		mode = 2;
		pin_low(RS_TXEN);
		pin_high(RS_RXEN);
		pin_low(LED_2);
		pin_high(IR_POWER_PIN);
		var_delay_ms(2000);
		pin_high(LED_2);
	}
}

int main(void)
{
	wdt_enable(WDTO_8S);
	board_init();
	var_delay_ms(100);
	hc_configure();
	unsigned int  delay                = 0;
	unsigned long delay_battery_report = 0;
    while (1) 
    {
		wdt_reset();
		select_mode();
		if(uart_received(1) && mode == 0){
			pin_low(LED_1);
			delay = 0;
			delay_battery_report = 0;
			uart_send(0, uart_get(1));
		}	
		if(uart_received(1) && mode == 1){
			pin_low(LED_3);
			delay = 0;
			delay_battery_report = 0;
			uart_send(0, uart_get(1));
		}
		if(uart_received(1) && mode == 2){
			pin_low(LED_2);
			delay = 0;
			delay_battery_report = 0;
			uart_send(0, uart_get(1));
		}

		if(uart_received(0) && mode == 1){
			pin_low(LED_1);
			delay = 0;
			delay_battery_report = 0;
			uart_send(1, uart_get(0));
		}
			
		if(uart_received(0) && mode == 2){
			pin_low(LED_2);
			pin_low(RS_TXEN);
			pin_high(RS_RXEN);
			var_delay_ms(1);
			uart_send(1, uart_get(0));
			var_delay_ms(1);
			pin_high(RS_TXEN);
			pin_low(RS_RXEN);
			delay = 0;
			delay_battery_report = 0;
		}
		if(delay++>50){
			pin_high(LED_1);
			pin_high(LED_2);
			pin_high(LED_3);
			delay = 0;
		}
		if(delay_battery_report++>500000){
			string_clear();
			string_add_string("Battery: ");
			string_add_float(battery_voltage(),2);
			string_add_string("V");
			hc_send_line(string_buffer);
			delay_battery_report = 0;
		}
    }
}

