#include <avr/sleep.h>
#define nop() asm volatile("nop")

boolean leds_on = true;
unsigned long badly_programmed_counter = 0;
int speedMultiplier = 1;

ISR(INT0_vect) {
  sleep_disable();
  leds_on = true;
}

void setup() {
  // put your setup code here, to run once:
  PORTB |= (1 << PB1); // input
  DDRB &= ~(1 << PB1);

  //shutdown_chip();
}

void loop() {

  if (leds_on)
  {
    cli();
    leds_on = false;
    badly_programmed_counter = 0;
  }

  if ( !(PINB & (1 << PB1)) )
  {

    badly_programmed_counter++;
//    if (badly_programmed_counter % 2 == 1)
//    {
//      charlie(10);
//    }
//    else
//    {
//      leds_off();
//    }
    delay(10);

    if (badly_programmed_counter >= 100)
    {
      speedMultiplier = badly_programmed_counter /100;
    }

    if(badly_programmed_counter >= 600)
    {
      badly_programmed_counter = 100;
      speedMultiplier = 1;
    }

    charlie(speedMultiplier);
    //delay(50);
  }
  else
  {
    animate_leds();
    badly_programmed_counter = 0;
  }
}

void shutdown_chip()
{
  leds_off();

  /* Clear WDRF in MCUSR */
  MCUSR &= ~(1 << WDRF);
  /* Write logical one to WDCE and WDE */
  /* Keep old prescaler setting to prevent unintentional time-out */
  WDTCR |= (1 << WDCE) | (1 << WDE);
  /* Turn off WDT */
  WDTCR = 0x00;

  ADCSRA &= ~(1 << ADEN); // turn off adc

  GIMSK |= (1 << INT0);
  GIMSK |= (1 << PCIE);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sei(); // Enable global interrupts
  sleep_cpu();
  sleep_disable();
}



void animate_leds()
{
  for (int i = 0; i < 12; i++) {
    led_pwm(i);
//    int ledTwo = i + 1;
//    if(ledTwo >= 12){
//      ledTwo = 0;
//    }
//    two_led_pwm(i, ledTwo);
    //delay(100);
  }

  for (int i = 0; i < 12; i++) {
    led_pwm(11-i);
//    int ledTwo = i - 1;
//    if(ledTwo < 0){
//      ledTwo = 11;
//    }
//    two_led_pwm(i, ledTwo);
    //delay(100);
  }
  
  led_pwm(11);
}

int ledOnTime = 4096;

void led_pwm(int i)
{
  int repeater = ledOnTime * speedMultiplier;
  for (int j=0; j<repeater; j++)
    {
      charlie(i);
      nop();
      nop();
      nop();
      nop();
      //delay(10);
      leds_off();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
    }
}

void two_led_pwm(int ledOne, int ledTwo)
{
  int repeater = ledOnTime * speedMultiplier;
  for (int j=0; j<repeater; j++)
    {
      charlie(ledOne);
      nop();
      nop();
      nop();
      nop();
      //delay(10);
      charlie(ledTwo);
      nop();
      nop();
      nop();
      nop();
      leds_off();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
    }
}

void leds_off()
{
  DDRB &= ~(
            (1 << PB0) |
            (1 << PB2) |
            (1 << PB3) |
            (1 << PB4)
          );
  PORTB &= ~(
             (1 << PB0) |
             (1 << PB2) |
             (1 << PB3) |
             (1 << PB4)
           );
}

void charlie (int var) {
  leds_off();

  switch (var) {
    case 0: // 1
      DDRB |= (1 << PB0) | (1 << PB2); // output
      PORTB |= (1 << PB0); // HIGH
      PORTB &= ~(1 << PB2); // LOW
      break;
    case 1: // 2
      DDRB |= (1 << PB0) | (1 << PB2); // output
      PORTB |= (1 << PB2); // HIGH
      PORTB &= ~(1 << PB0); // LOW
      break;
    case 2: // 3
      DDRB |= (1 << PB2) | (1 << PB3); // output
      PORTB |= (1 << PB2); // HIGH
      PORTB &= ~(1 << PB3); // LOW
      break;
    case 3: // 4
      DDRB |= (1 << PB2) | (1 << PB3); // output
      PORTB |= (1 << PB3); // HIGH
      PORTB &= ~(1 << PB2); // LOW
      break;
    case 4: // 5
      DDRB |= (1 << PB3) | (1 << PB4); // output
      PORTB |= (1 << PB3); // HIGH
      PORTB &= ~(1 << PB4); // LOW
      break;
    case 5: // 6
      DDRB |= (1 << PB3) | (1 << PB4); // output
      PORTB |= (1 << PB4); // HIGH
      PORTB &= ~(1 << PB3); // LOW
      break;
    case 6: // 7
      DDRB |= (1 << PB0) | (1 << PB3); // output
      PORTB |= (1 << PB0); // HIGH
      PORTB &= ~(1 << PB3); // LOW
      break;
    case 7: // 8
      DDRB |= (1 << PB0) | (1 << PB3); // output
      PORTB |= (1 << PB3); // HIGH
      PORTB &= ~(1 << PB0); // LOW
      break;
    case 8: // 9
      DDRB |= (1 << PB2) | (1 << PB4); // output
      PORTB |= (1 << PB2); // HIGH
      PORTB &= ~(1 << PB4); // LOW
      break;
    case 9: // 10
      DDRB |= (1 << PB2) | (1 << PB4); // output
      PORTB |= (1 << PB4); // HIGH
      PORTB &= ~(1 << PB2); // LOW
      break;
    case 10: // 11
      DDRB |= (1 << PB0) | (1 << PB4); // output
      PORTB |= (1 << PB0); // HIGH
      PORTB &= ~(1 << PB4); // LOW
      break;
    case 11: // 12
      DDRB |= (1 << PB0) | (1 << PB4); // output
      PORTB |= (1 << PB4); // HIGH
      PORTB &= ~(1 << PB0); // LOW
      break;
    default:
      ;
  }
}

