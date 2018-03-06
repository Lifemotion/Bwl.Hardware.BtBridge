#ifndef BOARD_H_
#define BOARD_H_

#define F_CPU 16000000

//Atmel Libraries
#include <util/delay.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/bwl_uart.h"
#include "../libs/bwl_simplserial.h"
#include "../libs/bwl_pins.h"
#include "../libs/bwl_strings.h"
#include "../libs/bwl_adc.h"
#include "../libs/bwl_hc05.h"

#define RS_TXEN			D,5
#define RS_RXEN			D,4
#define IR_POWER_PIN	B,3
#define IR_TX_PIN    	A,3
#define LED_3           A,1
#define LED_2           A,0
#define LED_1           A,2
#define BUTTON_1        B,0
#define BUTTON_2        B,1
#define BUTTON_MODE     B,2

#define HC_KEY          C,6

typedef unsigned char byte;
void  var_delay_ms(int ms);
void  board_init();
float battery_voltage();
#endif
