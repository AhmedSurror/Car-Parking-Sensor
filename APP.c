#include <avr/io.h>
#include <util/delay.h>
#include "buzzer.h"
#include "icu.h"
#include "lcd.h"
#include "leds.h"
#include "ultrasonic.h"

int main(void)
{
	Buzzer_init();
	LCD_init();
	LEDS_init();
	Ultrasonic_init();

	SREG |= (1<<7);

	uint16 distance = Ultrasonic_readDistance();

	LCD_displayString("Distance =    CM");

	for(;;)
	{
		distance = Ultrasonic_readDistance();

		Buzzer_off();
		LCD_moveCursor(0,0);
		LCD_displayString("Distance =    CM");
		LCD_moveCursor(0,11);
		LCD_intgerToString(distance);

		if(distance <10)
		{
			LCD_moveCursor(0,11);
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
		}

		LCD_moveCursor(0,11);
		LCD_intgerToString(distance);

		if(distance > 20)
		{
			LED_off(RED);
			LED_off(GREEN);
			LED_off(BLUE);
		}
		else if((distance >= 16) && (distance <= 20))
		{
			LED_on(RED);
			LED_off(GREEN);
			LED_off(BLUE);
		}
		else if((distance >= 11) && (distance <= 15))
		{
			LED_on(RED);
			LED_on(GREEN);
			LED_off(BLUE);
		}
		else if((distance >= 6) && (distance <= 10))
		{
			LED_on(RED);
			LED_on(GREEN);
			LED_on(BLUE);
		}
		else if(distance <= 5)
		{
			_delay_ms(1000);

			LCD_clearScreen();

			LCD_displayString("STOP!");

			LED_on(RED);
			LED_on(GREEN);
			LED_on(BLUE);

			Buzzer_on();
			_delay_ms(250);

			LED_off(RED);
			LED_off(GREEN);
			LED_off(BLUE);
			_delay_ms(250);
		}
	}
}

