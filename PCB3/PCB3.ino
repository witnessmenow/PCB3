/*******************************************************************
 *  Christmas 3 PCB - A Christmas tree shaped PCB
 *  
 *  12 Charlie-plexed LEDs running off an Attiny13
 *  
 *  By Brian Lough
 *  YouTube: https://www.youtube.com/brianlough
 *  Tindie: https://www.tindie.com/stores/brianlough/
 *  Twitch: https://twitch.tv/brianlough
 *  Twitter: @witnessmenow
 *******************************************************************/

#include <avr/sleep.h>
#define nop() asm volatile("nop")

#define MODE_AMOUNT 12
#define LED_ON_TIME 4096

boolean leds_on = true;
int badly_programmed_counter = 0;
int speedMultiplier = 1;
int mode = 0;

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
    delay(10);

    if (badly_programmed_counter >= 100)
    {
      mode++;
      badly_programmed_counter = 0;
    }

    if (mode >= MODE_AMOUNT)
    {
      mode = 0;
    }

    charlie(mode);
  }
  else
  {
    playAnimation();
    badly_programmed_counter = 0;
  }
}

void playAnimation() {
  switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      speedMultiplier = mode + 1;
      flashLeds(false);
      break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      speedMultiplier = mode - 4;
      flashLeds(true);
      break;
    case 10:
      lightAllLED();
      break;
    case 11:
      lightAllLED();
      leds_off();
      delay(100);
      break;
    default:
      ;
  }
}

void shutdown_chip() {
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



void flashLeds(bool twoLeds)
{
  for (int i = 0; i < 12; i++) {
    if (!twoLeds)
    {
      two_led_pwm(i, -1);
    } else {
      int ledTwo = i + 1;
      if (ledTwo >= 12) {
        ledTwo = 0;
      }
      two_led_pwm(i, ledTwo);
    }
  }

  for (int i = 0; i < 12; i++) {
    if (!twoLeds)
    {
      two_led_pwm(11 - i, -1);
    } else {
      int ledTwo = i - 1;
      if (ledTwo < 0) {
        ledTwo = 11;
      }
      two_led_pwm(i, ledTwo);
    }
  }

  two_led_pwm(11, -1);
}

void lightAllLED(){
  for (int j = 0; j < LED_ON_TIME; j++)
  {
    for(int i = 0; i < 12; i++)
    {
      charlie(i);
    }
  }
}

void two_led_pwm(int ledOne, int ledTwo)
{
  int repeater = LED_ON_TIME * speedMultiplier;
  for (int j = 0; j < repeater; j++)
  {
    charlie(ledOne);
    nop();
    nop();
    nop();
    
    if(ledTwo > -1){
      charlie(ledTwo);
    } else {
      leds_off();
    }

    nop();
    nop();
    nop();
    
    if(ledTwo > -1){
      leds_off();
    }
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

