#include <Arduino.h>
#include <limits.h>
#include <float.h>

const signed int  SINTMAX =  1000000;
const signed int  SINTMIN = -1000000;
const unsigned int UINTMAX = 2000000U;
const unsigned int UINTMIN = 0U;

int L1 = LED_BUILTIN;
unsigned long t_begin, t_end;
signed char   sca, scb;
unsigned char uca, ucb;
short         sa, sb;
unsigned short usa, usb;
int           sia, sib;
unsigned int  uia, uib;

float   fa, fb;

unsigned int n, i, j;
unsigned int sqn, oszto;

void IntTest() {
   Serial.print("\r\n");
   Serial.print("SCHAR_MIN = ");
   Serial.println(SCHAR_MIN);
   Serial.print("SCHAR_MAX = ");
   Serial.println(SCHAR_MAX);
   Serial.print("UCHAR_MAX = ");
   Serial.println(UCHAR_MAX);
   Serial.print("SHRT_MIN  = ");
   Serial.println(SHRT_MIN);
   Serial.print("SHRT_MAX  = ");
   Serial.println(SHRT_MAX);
   Serial.print("USHRT_MAX = ");
   Serial.println(USHRT_MAX);
   Serial.print("INT_MIN   = ");
   Serial.println(INT_MIN);
   Serial.print("INT_MAX   = ");
   Serial.println(INT_MAX);
   Serial.print("UINT_MAX  = ");
   Serial.println(UINT_MAX);
   Serial.print("LONG_MIN  = ");
   Serial.println(LONG_MIN);
   Serial.print("LONG_MAX  = ");
   Serial.println(LONG_MAX);
   Serial.print("ULONG_MAX = ");
   Serial.println(ULONG_MAX);
 //=========================================================================== 1.
// ===== Signed char add =====
   sca = SCHAR_MIN;
   scb = 1;
   t_begin = micros();
   while (sca < SCHAR_MAX)
   {
      sca = sca + scb;
   };
   t_end = micros();
   Serial.print(SCHAR_MAX - SCHAR_MIN);
   Serial.print(" operations\t");
   Serial.print("Signed Char ADD: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 2.
// ===== Signed char sub =====
   sca = SCHAR_MAX;
   scb = 1;
   t_begin = micros();
   while (sca > SCHAR_MIN)
   {
      sca = sca - scb;
   };
   t_end = micros();
   Serial.print(SCHAR_MAX - SCHAR_MIN);
   Serial.print(" operations\t");
   Serial.print("Signed Char SUB: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 3.
// ===== Unsigned char add =====
   uca = 0;
   ucb = 1;
   t_begin = micros();
   while (uca < UCHAR_MAX)
   {
      uca = uca + ucb;
   };
   t_end = micros();
   Serial.print(UCHAR_MAX);
   Serial.print(" operations\t");
   Serial.print("Unsigned Char ADD: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 4.
// ===== Unsigned char sub =====
   uca = UCHAR_MAX;
   ucb = 1;
   t_begin = micros();
   while (uca > 0)
   {
      uca = uca - ucb;
   };
   t_end = micros();
   Serial.print((unsigned long)UCHAR_MAX);
   Serial.print(" operations\t");
   Serial.print("Unsigned Char SUB: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 5.
// ===== Signed short add =====
   sa = SHRT_MIN;
   sb = 1;
   t_begin = micros();
   while (sa < SHRT_MAX)
   {
      sa = sa + sb;
   };
   t_end = micros();
   Serial.print((unsigned long)(SHRT_MAX - SHRT_MIN));
   Serial.print(" operations\t");
   Serial.print("Signed Short ADD: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 6.
// ===== Signed short sub =====
   sa = SHRT_MAX;
   sb = 1;
   t_begin = micros();
   while (sa > SHRT_MIN)
   {
      sa = sa - sb;
   };
   t_end = micros();
   Serial.print((unsigned long)(SHRT_MAX - SHRT_MIN));
   Serial.print(" operations\t");
   Serial.print("Signed Short SUB: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 7.
// ===== Unsigned short add =====
   usa = 0;
   usb = 1;
   t_begin = micros();
   while (usa < USHRT_MAX)
   {
      usa = usa + usb;
   };
   t_end = micros();
   Serial.print((unsigned long)USHRT_MAX);
   Serial.print(" operations\t");
   Serial.print("Unsigned Short ADD: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 8.
// ===== Unsigned short sub =====
   usa = USHRT_MAX;
   usb = 1;
   t_begin = micros();
   while (usa > 0)
   {
      usa = usa - usb;
   };
   t_end = micros();
   Serial.print((unsigned long)USHRT_MAX);
   Serial.print(" operations\t");
   Serial.print("Unsigned Short SUB: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 9.
// ===== Signed int add =====
   sia = SINTMIN;
   sib = 1;
   t_begin = micros();
   while (sia < SINTMAX)
   {
      sia = sia + sib;
   };
   t_end = micros();
   Serial.print((unsigned long)(SINTMAX - SINTMIN));
   Serial.print(" operations\t");
   Serial.print("Signed Int ADD: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 10.
// ===== Signed int sub =====
   sia = SINTMAX;
   sib = 1;
   t_begin = micros();
   while (sia > SINTMIN)
   {
      sia = sia - sib;
   };
   t_end = micros();
   Serial.print((unsigned long)(SINTMAX - SINTMIN));
   Serial.print(" operations\t");
   Serial.print("Signed Int SUB: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 11.
// ===== Unsigned int add =====
   uia = UINTMIN;
   uib = 1;
   t_begin = micros();
   while (uia < UINTMAX)
   {
      uia = uia + uib;
   };
   t_end = micros();
   Serial.print((unsigned long)UINTMAX);
   Serial.print(" operations\t");
   Serial.print("Unsigned Int ADD: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 12.
// ===== Unsigned int sub =====
   uia = UINTMAX;
   uib = 1;
   t_begin = micros();
   while (uia > UINTMIN)
   {
      uia = uia - uib;
   };
   t_end = micros();
   Serial.print((unsigned long)UINTMAX);
   Serial.print(" operations\t");
   Serial.print("Unsigned Int SUB: ");
   Serial.println(t_end - t_begin);
}

/*
 * ===========================================================================
 *        FloatTest
 * ===========================================================================
 */
void FloatTest() {
   Serial.print("FLT_DIG = ");
   Serial.println(FLT_DIG);
   Serial.print("DECIMAL_DIG = ");
   Serial.println(__DECIMAL_DIG__);
//=========================================================================== 1.
// ===== Float add =====
   fa = -100.0;
   fb = 0.001;
   t_begin = micros();
   while (fa < 100.0f)
   {
      fa = fa + fb;
   };
   t_end = micros();
   Serial.print(20000);
   Serial.print(" operations\t");
   Serial.print("Float ADD: ");
   Serial.println(t_end - t_begin);
//=========================================================================== 2.
// ===== Float sub =====
   fa = 100.0;
   fb = 0.001;
   t_begin = micros();
   while (fa > -100.0)
   {
      fa = fa - fb;
   };
   t_end = micros();
   Serial.print(20000);
   Serial.print(" operations\t");
   Serial.print("Float SUB: ");
   Serial.println(t_end - t_begin);
}

/*
 * ===========================================================================
 *        PrimeTest
 * ===========================================================================
 */
void PrimeTest() {
   t_begin = micros();
   j = 0;
   for (n=2; n<=1000000; n++)
   {
      sqn = sqrt((double)n);
      for(i=2; i<=sqn; i++)
      {
         oszto = 0;
         if(n % i == 0)
         {
            oszto = i;
            break;
         }
      };
      if (oszto == 0)
         j++;
   };
   t_end = micros();
   Serial.print(j);
   Serial.print(" primes found \t");
   Serial.print("Prime test: ");
   Serial.println(t_end - t_begin);
   Serial.print("End of job\r\n");
} 

void setup()
{
   sleep_ms(5000);   /* wait to start the terminal */
   Serial.begin(9600);
   sleep_ms(5000);   /* wait for start the UART properly */
   gpio_set_function(L1, GPIO_FUNC_SIO);
   gpio_set_dir(L1, OUTPUT);
   L1 = HIGH;
   IntTest();
   FloatTest();
   PrimeTest();
   L1 = LOW; 
}

void loop()
{

}