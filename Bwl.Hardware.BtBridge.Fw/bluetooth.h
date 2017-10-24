/*
 * HC_05h.h
 *
 * Created: 20.03.2017 23:50:32
 *  Author: bessgusev
 */ 

#include <avr/io.h>

#define BLUETOOTH_NAME     "OrlanBridge"
#define BLUETOOTH_PASSWORD "0000"

#define KEY_PORT    PORTC
#define KEY_DDR     DDRC
#define KEY_PIN     1

#define RESET_PORT  PORTC
#define RESET_DDR   DDRC
#define RESET_PIN   0

#define HC_UART     0
#define KEY_LOW    {KEY_DDR |= (1<<KEY_PIN); KEY_PORT &= ~(1<<KEY_PIN);}
#define KEY_HIGH   {KEY_DDR |= (1<<KEY_PIN); KEY_PORT |= (1<<KEY_PIN) ;}
#define RESET_LOW  {RESET_DDR |= (1<<RESET_PIN); RESET_PORT &= ~(1<<RESET_PIN);}
#define RESET_HIGH {RESET_DDR |= (1<<RESET_PIN); RESET_PORT |= (1<<RESET_PIN) ;}

void hc_configure();
void cmd_handler(unsigned char cmd);
void hc_send_byte  (char data);
void hc_send_string(char *string);
void hc_send_line  (char *string);
//must be realised
void var_delay_ms(int ms);
