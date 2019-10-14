#include <avr/io.h> 
#include <util/delay.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include "LCD.h"

void DisplayResult()
void CalculateResult()
void pushBut()
void Circ_Init(void);
int Number;
int Num1;
int Num2;
char action[10];
bool result = false;

int main(void)
{
	Circ_Init(); // Initialize the circuit
	LCD_Init(); // initialize LCD controller
	while(1)
	{
		if (result==true){
			CalculateResult();
            DisplayResult(); 
		}  
	}
	
}		
		  
void Circ_Init(void)
{
	
	// Use PB pins for LCD interface
	// Use PD pins for rows
	// Use PC pins for coloumns 
 
	DDRB = 0xFF; // 1111.1111; set PB0-PB7 as outputs	 
	DDRD=0b00000000; // Set PD4-PD7 as i/p
	DDRC=0xFF;// Set PC0-PC5 as o/p
	PORTD = 0xFF;    //enable all internal pull-ups  
	return;

}

void pushBut()
{
	PORTC = 0b00000000;// Turn all rows to LOW
	PORTD = 0b11110000;// Enable Pull-ups
	
	//Check which coloumn has LOW i/p	
	if (!(PIND & (1<<PD4)))
	{
		// Change corresponding rows and check the i/p
		PORTC=0b00001110;
		PORTC=PORTC;
		if (!(PIND & (1<<PD4))){
		LCD_Integer(1);
	      if (Number==0)
          Number=1;
          else
          Number = (Number*10) + 1;
		PORTC=0b00001101;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD4))){
		LCD_Integer(2);
		 if (Number==0)
         Number=2;
         else
         Number = (Number*10) + 2;
		PORTC=0b00001011;
		PORTC=PORTC;
	    }

		if (!(PIND & (1<<PD4))){
		LCD_Integer(3);
		  if (Number==0)
          Number=3;
          else
          Number = (Number*10) + 3;
		PORTC=0b00000111;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD4))){
		LCD_Char('+');
		action = '+';
	    }

	}
	else if (!(PIND & (1<<PD5)))
	{
		PORTC=0b00001110;
		PORTC=PORTC;
		if (!(PIND & (1<<PD5))){
		LCD_Integer(4);
		 if (Number==0)
         Number=4;
         else
         Number = (Number*10) + 4;
		PORTC=0b00001101;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD5))){
		LCD_Integer(5);
		 if (Number==0)
         Number=5;
         else
         Number = (Number*10) + 5;
		PORTC=0b00001011;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD5))){
		LCD_Integer(6);
		 if (Number==0)
         Number=6;
         else
         Number = (Number*10) + 6;
		PORTC=0b00000111;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD5))){
		LCD_Char('-');
		action = '-'
	    }
	}
	
	else if (!(PIND & (1<<PD6)))
	{
		PORTC=0b00001110;
		PORTC=PORTC;
		if (!(PIND & (1<<PD6))){
		LCD_Integer(7);
		 if (Number==0)
         Number=7;
         else
         Number = (Number*10) + 7;
		PORTC=0b00001101;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD6))){
		LCD_Integer(8);
		 if (Number==0)
         Number=8;
         else
         Number = (Number*10) + 8;
		PORTC=0b00001011;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD6))){
		LCD_Integer(9);
		 if (Number==0)
         Number=9;
         else
         Number = (Number*10) + 9;
		PORTC=0b00000111;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD6))){
		LCD_Char('x');
		action = '*'
	    }

	}
	
	else if (!(PIND & (1<<PD7)))
	{
		PORTC=0b00001110;
		PORTC=PORTC;
		if (!(PIND & (1<<PD7))){
		Num2=Number;
        result = true;
		PORTC=0b00001101;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD7))){
		LCD_Integer(0);
	      if (Number==0)
          Number=0;
          else
          Number = (Number*10) + 0;
		PORTC=0b00001011;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD7))){
		LCD_Clear();
		PORTC=0b00000111;
		PORTC=PORTC;
	    }
		if (!(PIND & (1<<PD7))){
		LCD_Char('/');
		action = '/'
	    }
	}
	return 'n';           	// Means no key has been pressed
}

void CalculateResult()
{
if (action=='+')
Number = Num1+Num2;

if (action=='-')
Number = Num1-Num2;

if (action=='*')
Number = Num1*Num2;

if (action=='/')
Number = Num1/Num2; 
}

void DisplayResult()
{
if (result==true){
LCD_Char('=');
} //Display the result

LCD_Cmd(0xC0);   // set the cursor to line 2
LCD_Integer(Number); //Display the result
}



	
	