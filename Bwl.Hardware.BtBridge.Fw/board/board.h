#ifndef BOARD_H_
#define BOARD_H_

#define F_CPU 8000000UL

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
#include "../bluetooth.h"
#define RS_TXEN			D,5
#define RS_RXEN			D,4
#define IR_POWER_PIN	B,7
#define LED_3           A,1
#define LED_2           A,0
#define LED_1           C,6
#define BUTTON_1        A,3
#define BUTTON_2        A,2

typedef unsigned char byte;
void  var_delay_ms(int ms);
void  board_init();
float battery_voltage();
#endif
