#include <SPI.h>

#define SS1 4
#define SS2 5

void setup (void)
{
  pinMode(SS1, OUTPUT);
  digitalWrite(SS1, HIGH);
  pinMode(SS2, OUTPUT);
  digitalWrite(SS2, HIGH);

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV16);

}  // end of setup


void loop (void)
{

  char c;

  // enable Slave Select
  digitalWrite(SS1, LOW);    // SS is pin 10

  // send test string
  for (const char * p = "Hello world!\n" ; c = *p; p++)
    SPI.transfer (c);

  // disable Slave Select
  digitalWrite(SS1, HIGH);

  delay (1000);
}  // end of loop
