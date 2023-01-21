/*
 * main.cpp
 *
 *  Created on: 2 Jan 2023
 *      Author: monic
 */

#include <LiquidCrystal.h>
#include "Arduino.h"
#include "HD44780.hpp"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.hpp"

#define btnN 5
#define btnR 0
#define btnU 1
#define btnD 2
#define btnL 3
#define btnS 4

uint16_t raw;

const int rs = 8, en = 9, d4 = 4, d5 = 5,d6 = 6, d7 = 7;

char com[4][6] = {"play\r\n","stop\r\n","next\r\n","prev\r\n"};

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte Fig1[] = {
		B10000,
		B01010,
		B00111,
		B00010,
		B00011,
		B00010,
		B00101,
		B01001
};

byte Fig2[] = {
		B00000,
		B00010,
		B00111,
		B01010,
		B00111,
		B00010,
		B00101,
		B01000,
};

byte Fig3[] = {
		B00001,
		B00101,
		B01110,
		B10100,
		B01100,
		B00100,
		B01010,
		B01001
};

byte Fig4[] = {
		B00000,
		B00100,
		B01110,
		B10101,
		B01100,
		B01010,
		B10001
};

// start should be 0 or 1
void write_step(int step, int start) {
	lcd.clear();
	// 1. display blinking diode
	if ((PIND & 1<<PIND3)){   // 00001111 & 00000001<<3  =>  00001111 & 00001000 => 00001000 => 1
		PORTB ^= (1 << PORTB2);
		_delay_ms(100);
	}
	else {
		int level = 0;
		for(int n=0;n<8;n++) {
		  lcd.setCursor(n*2+start,0);
		  lcd.write(byte(step));
		}
		level++;
		for(int n=0;n<8;n++) {
		  lcd.setCursor(n*2+start,1);
		  lcd.write(byte(step));
		}

		_delay_ms(500);
	}

}

void setup() {

	  // Serial.begin(9600);
	  // 9600 bps - transmission speed
	  uart_init(9600,0);
	  sei();
	  // Specify the LCD's number of columns and rows:
	  lcd.begin(16, 2);
	  lcd.clear();

	  // Create new characters:
	  lcd.createChar(0, Fig1);
	  lcd.createChar(1, Fig2);
	  lcd.createChar(2, Fig3);
	  lcd.createChar(3, Fig4);

	  // LEDS CONTROLLER
	  DDRB |= (1<<DDB2) | (1<<DDB3) | (1<<DDB4) | (1<<DDB5);            // xx1111xx << Direction of port line (1 - output)
	  PORTB |= (1<<PORTB2) | (1<<PORTB3) | (1<<PORTB4) | (1<<PORTB5);   // xx1111xx <<  Output register (1 - do not light)
	  // buttons
	  DDRD &= ~(1<<DDD0) | ~(1<<DDD1) | ~(1<<DDD2) | ~(1<<DDD3);   	  // xxxx0000 << Direction of port line (0 - input)
//	  digitalWrite(btnU,HIGH);
//	  digitalWrite(btnD,HIGH);

}

void display_blinking() {
	// 1. display blinking diode
	if (!(PIND & 1<<PIND3)){   // 00001111 & 00000001<<3  =>  00001111 & 00001000 => 00001000 => 1
		PORTB ^= (1 << PORTB2);
		_delay_ms(100);
	}
}

int getButton() {
	int b= analogRead(0);
	if (b>1000) return btnN;
	if (b<50) return btnR;
	if (b<180) return btnU;
	if (b<330) return btnD;
	if (b<520) return btnL;
	if (b<700) return btnS;
	return btnN;
}

int getButton2() {
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	raw = ADC;
	/*
				RIGHT		0
				UP 		131
				DOWN		306
				LEFT		480
				SELECT	721
			*/

	// UP
	if ((100 < raw) && (raw < 250) ) {
		return btnU;
	}
	// DOWN
	if ((250 < raw) && (raw < 350)) {
		return btnD;
	}
	// RIGHT
	if ((0 < raw) && (raw < 100)) {
		return btnR;
	}
	// LEFT
	if (( 350< raw) && (raw < 550)) {
		return btnL;
	}
	// SELECT
	if (( 550< raw) && (raw < 750)) {
		return btnS;
	}
	// NONE
	return btnN;
	_delay_ms(200);
}

void loop() {
	while(1) {
		display_blinking();
		write_step(0,0);
		display_blinking();
	    write_step(1,0);
	    display_blinking();
		write_step(2,1);
		display_blinking();
		write_step(3,1);
		uart_send_string((unsigned char*)"start\r\n");

		int chosen = getButton2();
		if(chosen == btnS)	uart_send_string((unsigned char*)com[0]);
		else
			if(chosen == btnU)	uart_send_string((unsigned char*)com[2]);
			else
				if(chosen == btnD)	uart_send_string((unsigned char*)com[3]);
				else
					if(chosen == btnL || chosen == btnR) {
						uart_send_string((unsigned char*)com[1]);
						write_step(1,0);
						delay(1000);
					}
					else
						if(chosen == btnN) {
							uart_send_string((unsigned char*)"No button");
						}
	}
}

int main() {
	setup();
	loop();
}




