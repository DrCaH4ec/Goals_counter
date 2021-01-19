#ifndef LIBS_H
#define LIBS_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "seg7.h"

//////////settings of 7 segments indicator
#define SEG_A_PORT PORTD
#define SEG_A_n 0

#define SEG_B_PORT PORTD
#define SEG_B_n 1

#define SEG_C_PORT PORTD
#define SEG_C_n 4

#define SEG_D_PORT PORTD
#define SEG_D_n 5

#define SEG_E_PORT PORTD
#define SEG_E_n 6

#define SEG_F_PORT PORTD
#define SEG_F_n 7

#define SEG_G_PORT PORTB
#define SEG_G_n 0

#define DIG_1_PORT PORTB
#define DIG_1_n 5

#define DIG_2_PORT PORTC
#define DIG_2_n 0

#define DIG_3_PORT PORTB
#define DIG_3_n 4

#define DIG_4_PORT PORTB
#define DIG_4_n 3

#define DIG_5_PORT PORTB
#define DIG_5_n 2

#define DIG_6_PORT PORTB
#define DIG_6_n 1

#define PITCH_1_LED_PORT PORTC
#define PITCH_1_LED_n 2

#define PITCH_2_LED_PORT PORTC
#define PITCH_2_LED_n 3

#define BOOZER_PORT PORTC
#define BOOZER_n 1

#define TIME_OF_BUTTON_BEEP 100

#define MINUS_2_BUTTON_PIN PINC
#define MINUS_2_BUTTON_n 4

#define TIME_OF_BUTTON_PAUSE 250 //in MILIseconds

#define TIME_OF_SWITCH_DIGIT 1 //in MILIseconds

#define TIME_OF_RST 1500 //in MILIseconds

#define MINUS_1_BUTTON_PIN PINC
#define MINUS_1_BUTTON_n 5


#endif