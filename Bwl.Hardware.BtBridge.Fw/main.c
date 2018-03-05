#include "board/board.h"

#define BUFFER_SIZE 750

unsigned char rx_buffer[BUFFER_SIZE];
unsigned int  rx_buffer_cursor   = 0;

unsigned char tx_buffer[BUFFER_SIZE];
unsigned int  tx_buffer_cursor   = 0;
unsigned char mode = 0;
void ir_receiver_mode()
{
	pin_high(RS_TXEN);
	pin_low(LED_2);
	pin_low(IR_POWER_PIN);
	var_delay_ms(100);
	pin_high(LED_2);
	uart_init_withdivider(1, F_CPU/16/2400  -1);
	uart_send_string(0, "IR mode enabled."); 
	mode = 1;
}

void sserial_tx_mode(){
	pin_high(RS_TXEN);
	pin_high(RS_RXEN);
}

void sserial_rx_mode()
{
	pin_low(RS_TXEN);
	pin_low(RS_RXEN);
}

void serial_transmitter_mode()
{
	sserial_rx_mode();
	pin_low(LED_2);
	pin_high(IR_POWER_PIN);
	var_delay_ms(100);
	pin_high(LED_2);
	uart_init_withdivider(1, F_CPU/16/38400  -1); 
	uart_send_string(0, "Serial mode."); 
	mode = 2;

}

void select_mode()
{	
	if(pin_get_in(BUTTON_1)==0 || pin_get_in(BUTTON_2)==0)var_delay_ms(1500);//Антидребезг
	if(pin_get_in(BUTTON_1)==0 && pin_get_in(BUTTON_2)==0){
		uart_init_withdivider(1, 12);
		uart_send_string(0, "Select baudrate:\r\n"); 
		uart_send_string(0, "1) 2400\r\n");  
		uart_send_string(0, "2) 4800\r\n"); 
		uart_send_string(0, "3) 9600\r\n");  
		uart_send_string(0, "4) 14400\r\n"); 
		uart_send_string(0, "5) 19200\r\n"); 
		uart_send_string(0, "6) 28800\r\n"); 
		uart_send_string(0, "7) 38400\r\n"); 
		uart_send_string(0, "8) 56000\r\n");
		char response = 0;
		while(response<0x30 || response>0x39){
			if(uart_received(0))response = uart_get(0);
			wdt_reset();
		}
		
		switch(response)
		{				
			case '1': uart_init_withdivider(1, F_CPU/16/2400  -1); uart_send_string(0, "2400"); break;
			case '2': uart_init_withdivider(1, F_CPU/16/4800  -1); uart_send_string(0, "4800"); break;
			case '3': uart_init_withdivider(1, F_CPU/16/9600  -1); uart_send_string(0, "9600"); break;
			case '4': uart_init_withdivider(1, F_CPU/16/14400 -1); uart_send_string(0, "14400"); break;
			case '5': uart_init_withdivider(1, F_CPU/16/19200 -1); uart_send_string(0, "19200"); break;
			case '6': uart_init_withdivider(1, F_CPU/16/28800 -1); uart_send_string(0, "28800"); break;
			case '7': uart_init_withdivider_x2(1, F_CPU/8/38400  -1); uart_send_string(0, "38400"); break;
			case '8': uart_init_withdivider_x2(1, F_CPU/8/56000  -1); uart_send_string(0, "56000"); break;
		}
		uart_send_string(0, "\r\n");
	} else if(pin_get_in(BUTTON_1)==0){		
		ir_receiver_mode();
	} else if(pin_get_in(BUTTON_2)==0){
		serial_transmitter_mode();
	}
}

int main(void)
{
	wdt_enable(WDTO_8S);
	wdt_reset();
	board_init();
	serial_transmitter_mode();
	unsigned int rx_serial_delay = 0;
	unsigned int tx_serial_delay = 0;
    while (1) 
    {
		wdt_reset();
		select_mode();
		//ИК мост
		sserial_rx_mode();
		if(uart_received(1) && mode==1){
			pin_low(LED_2);
			uart_send(0, uart_get(1));
			pin_high(LED_2);
		}
		//последовательный прием
		if(uart_received(1) && mode == 2 && tx_buffer_cursor<BUFFER_SIZE){
			tx_buffer[tx_buffer_cursor++] = uart_get(1);
			tx_serial_delay = 4500;
		}
		if(tx_serial_delay == 0 && tx_buffer_cursor>0){
			for(int i=0;i<tx_buffer_cursor;i++){
				uart_send(0, tx_buffer[i]);
				var_delay_ms(1);
				wdt_reset();
			}
			tx_buffer_cursor = 0;
		}		
		if(uart_received(0) && mode == 2 && rx_buffer_cursor<BUFFER_SIZE){
			rx_buffer[rx_buffer_cursor++] = uart_get(0);
			rx_serial_delay = 3500;
		}		
		if(rx_serial_delay == 0 && rx_buffer_cursor>0){
			sserial_tx_mode();
			var_delay_ms(1);
			for(int i=0;i<rx_buffer_cursor;i++){
				uart_send(1, rx_buffer[i]);	
			}
			rx_buffer_cursor = 0;
			var_delay_ms(1);
			sserial_rx_mode();
		}
		if(rx_serial_delay>0)rx_serial_delay--;
		if(tx_serial_delay>0)tx_serial_delay--;
    }
}

