/*
 * main.c
 *
 * Created: 12/04/2021 4:08 PM
 * Author: Mahmoud Abd Elmonem
 */

#ifndef __AVR_ATmega32__
#define __AVR_ATmega32__
#endif

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char firstDigit = 0, secondDigit = 0, lim = 10;
	DDRD = DDRD & (~(1 << PD4));
	DDRC |= 0xFF;

	PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3));

	while (1)
	{
		if (PIND & (1 << PD4))
		{
			_delay_ms(30);
			if (PIND & (1 << PD4))
			{
				firstDigit += 1;
				secondDigit += firstDigit == 10;
				firstDigit = firstDigit >= 10 ? firstDigit - 10 : firstDigit;
				secondDigit = secondDigit >= 10 ? secondDigit - 10 : secondDigit;
				PORTC = (PORTC & 0xF0) | (firstDigit & 0x0F);
				PORTC = (PORTC & 0x0F) | ((secondDigit << 4) & 0xF0);
			}
			while (PIND & (1 << PD4))
			{
			} // wait until switch is released
		}
	}
}