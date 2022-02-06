#include <Arduino.h>

#include <UTFT.h>
#include <UTouch.h>

extern uint8_t BigFont;
extern uint8_t SevenSegNumFont;

UTFT myGLCD(ITDB24E_8,19,18,17,16);
UTouch myTouch(15,8,14,9,20);

int x,y;
void setup()
{
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(“OZ8CW”,CENTER,100);
  myGLCD.print(“Super Keyer”,CENTER,130);
  delay(1000);
  myGLCD.clrScr();
  myTouch.InitTouch(PORTRAIT);
  myTouch.setPrecision(PREC_LOW);
}

void message(int tal)
{
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.printNumI(tal,CENTER,270);
  myGLCD.setFont(BigFont);
}

void knap1()
{
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect(5,5,235,59);
  myGLCD.print(“Knap 1”,80,25);
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
    if(x>5 && x<235 && y>5 && y<59)
    {
      myGLCD.clrScr();
      delay(100);
      message(1);
      knap2();
    }
  }
}


void knap2()
{
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect(5,69,235,123);
  myGLCD.print(“Knap 2”,CENTER,87);
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
    if(x>5 && x<235 && y>69 && y<123)
    {
      myGLCD.clrScr();
      delay(100);
      message(2);
      knap3();
    }
  }
}


void knap3(){
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect(5,133,235,187);
  myGLCD.print(“Knap 3”,CENTER,150);
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
    if(x>5 && x<235 && y>133 && y<187)
    {
      myGLCD.clrScr();
      delay(100);
      message(3);
      knap4();
    }
  }
}

void knap4(){
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect(5,197,235,251);
  myGLCD.print(“Knap 4”,CENTER,215);
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
    x=myTouch.getX();
    y=myTouch.getY();
    if(x>5 && x<235 && y>197 && y<251)
    {
      myGLCD.clrScr();
      delay(100);
      message(4);
      knap1();
    }
  }
}

void loop()
{
  knap1();
}
