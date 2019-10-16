#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <LCD.h>
#include <math.h>
#include <stdio.h>



typedef enum { false, true } bool;
double Number = 0;
double Num1;
double Num2;
char action;
char op;
char key;
int k =0;


 
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

char READ_SWITCHES()
{
PORTC = 0b00000000;// Turn all rows to LOW
PORTD = 0b11110000;// Enable Pull-ups

//Check which coloumn has LOW i/p
if (!(PIND & (1<<PD4)))
{
// Change corresponding rows and check the i/p
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '1';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '2';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '3';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD4)))
return '+';
}
else if (!(PIND & (1<<PD5)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '4';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '5';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '6';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD5)))
return '-';
}

else if (!(PIND & (1<<PD6)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '7';
PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '8';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '9';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD6)))
return '*';
}

else if (!(PIND & (1<<PD7)))
{
PORTC=0b00001110;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return '=';

PORTC=0b00001101;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return '0';
PORTC=0b00001011;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return 'c';
PORTC=0b00000111;
PORTC=PORTC;
if (!(PIND & (1<<PD7)))
return '/';
}



return 'n';           // Means no key has been pressed
}




char get_key(void)
{
key = 'n';
while(key=='n')
{
key=READ_SWITCHES();
}
return key;
}

void DetectButtons()
{
char key=get_key();

   
     if (key == '1') //If Button 1 is pressed
    {
    if (Number==0)
    Number=1;
    else
    Number = (Number*10) + 1; //Pressed twice
    }
   
     if (key == '4') //If Button 4 is pressed
    {
    if (Number==0)
    Number=4;
    else
    Number = (Number*10) + 4; //Pressed twice
    }
   
     if (key == '7') //If Button 7 is pressed
    {
    if (Number==0)
    Number=7;
    else
    Number = (Number*10) + 7; //Pressed twice
    }
    
    if (key == '0')
    { //Button 0 is Pressed
    if (Number==0)
    Number=0;
    else
    Number = (Number*10) + 0; //Pressed twice
    }
    
     if (key == '2') //Button 2 is Pressed
    {
     if (Number==0)
    Number=2;
    else
    Number = (Number*10) + 2; //Pressed twice
    }
   
     if (key == '5')
    {
     if (Number==0)
    Number=5;
    else
    Number = (Number*10) + 5; //Pressed twice
    }
   
     if (key == '8')
    {
     if (Number==0)
    Number=8;
    else
    Number = (Number*10) + 8; //Pressed twice
    }  
 

    if (key == '=')
    {
    Num2=Number;
    }
   
     if (key == '3')
    {
     if (Number==0)
    Number=3;
    else
    Number = (Number*10) + 3; //Pressed twice
    }
   
     if (key == '6')
    {
    if (Number==0)
    Number=6;
    else
    Number = (Number*10) + 6; //Pressed twice
    }
   
     if (key == '9')
    {
    if (Number==0)
    Number=9;
    else
    Number = (Number*10) + 9; //Pressed twice
    }  

      if (key == '+' || key == '-' || key == '*' || key == '/') //Detecting Buttons on Column 4
  {

    if (key == '+')
    {action = '+';}
     if (key == '-')
    {action = '-'; }
     if (key == '*')
    {action = '*';}
     if (key == '/')
    {action = '/';}
      

  }
 
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


int main(void)
{
Circ_Init(); // Initialize the circuit
LCD_Init(); // initialize LCD controller

while(1)
{
key=get_key();

if (key == 'b')  
 {
  LCD_Cmd(0x10);
  LCD_Char(' ');
  LCD_Cmd(0x10); 
}

if (key != 'b')  
{
LCD_Char(key);
}

DetectButtons();

if(key == 'c'){
LCD_Clear();
Number =0;
Num1=0;
Num2=0;
k=0;
}

if(key == '='){
LCD_Cmd(0xC0);
CalculateResult();
LCD_Message(DoubleToStr(Number));
}

 if (key == '+' || key == '-' || key == '*' || key == '/') //Detecting Buttons on Column 4
  {
if(k == 0){
    Num1 = Number;    
    Number =0;
    k = 1;
    op = key;
}

else{
Num2 = Number;
  if (op=='+')
    Number = Num1+Num2;


  if (op=='-')
    Number = Num1-Num2;


  if (op=='*')
    Number = Num1*Num2;


  if (op=='/')
    Number = Num1/Num2;
LCD_Clear();
LCD_Message(DoubleToStr(Number));
LCD_Char(key);
Num1 = Number;
op = key;

}
Number = 0;
  }

_delay_ms(300);
}

}
