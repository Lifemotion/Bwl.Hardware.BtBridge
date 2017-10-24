/*
 * CFile1.c
 *
 * Created: 20.03.2017 23:50:14
 *  Author: gus10
 */ 


#include "bluetooth.h"
#include "./libs/bwl_uart.h"
#include "board/board.h"
#include <avr/interrupt.h>

void hc_send_string(char *string)
{
	unsigned	char  i=0;
	while (string[i]>0 && i<200)
	{
		uart_send(HC_UART,string[i]);
		i++;
	}
}


void hc_send_byte(char data)
{
	uart_send(HC_UART,data);
}


void hc_send_line(char *string)
{
	hc_send_string(string);
	uart_send(HC_UART, 0xD);
	uart_send(HC_UART, 0xA);
}


void hc_configure()
{
	KEY_LOW;
	uart_init_withdivider(HC_UART, GET_UBRR(F_CPU, 9600));
	var_delay_ms(2000);
	KEY_HIGH;
	var_delay_ms(200);
	hc_send_line("AT+RMAAD");
	var_delay_ms(200);
	hc_send_line("AT+ROLE=0");
	var_delay_ms(200);
	hc_send_string("AT+NAME=");
	hc_send_line(BLUETOOTH_NAME);
	var_delay_ms(200);
	hc_send_string("AT+PSWD=");
	hc_send_line(BLUETOOTH_PASSWORD);
	var_delay_ms(200);
	hc_send_line("AT+RESET");
	KEY_LOW;
}
