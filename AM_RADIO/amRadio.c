/*
Plays a simple tune, broadcasts it in the AM radio band. Tune to 1Mhz AM.
This text describes the basic setup details to use the AM Radio transmitter. It is very simple:
Note: the code and setup was done with the ATmega168.
All you need to do is to connect a 3 foot long 22-guage wire to PD5 and flash in the code to use it.
I will not include any schematics here because I am assuming that you know how to make basic power connetions with the AVR.
Then following the power delivery connections to the AVR, you can then connect an antenna to pin PD5 as described above.
After this is done, tune your radio to AM 1Mhz to listen to the tunes being played.
*/

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#include <avr/power.h>
#include <avr/interrupt.h>
#include "pitches.h"


static inline void initTimer0(void) {
  TCCR0A |= (1 << WGM01);                                  /* CTC mode */
  TCCR0A |= (1 << COM0B0);            /* Toggles pin each time through */
  TCCR0B |= (1 << CS00);              /* Clock at CPU frequency, ~8MHz */
  OCR0A = 3;                          /* carrier frequency */
}

static inline void initTimer1(void) {
  TCCR1B |= (1 << WGM12);                                  /* CTC mode */
  TCCR1B |= (1 << CS11);            /* Clock at CPU/8 frequency, ~1MHz */
  TIMSK1 |= (1 << OCIE1A);          /* enable output compare interrupt */
}

ISR(TIMER1_COMPA_vect) {                 /* ISR for audio-rate Timer 1 */
  DDRD ^= (1 << PD5);          /* toggle carrier on and off */
}

static inline void transmitBeep(uint16_t pitch, uint16_t duration) {
  OCR1A = pitch;                               /* set pitch for timer1 */
  sei();                                         /* turn on interrupts */
  do {
    _delay_ms(1);                            /* delay for pitch cycles */
    duration--;
  } while (duration > 0);
  cli();                  /* and disable ISR so that it stops toggling */
  DDRD |= (1 << PD5);               /* back on full carrier */
}

int main(void) {
  // -------- Inits --------- //

  clock_prescale_set(clock_div_1);                  /* CPU clock 8 MHz */
  initTimer0();
  initTimer1();

  // ------ Event loop ------ //
  while (1) {

    transmitBeep(E3, 200);
    _delay_ms(100);
    transmitBeep(E3, 200);
    _delay_ms(200);
    transmitBeep(E3, 200);
    _delay_ms(200);
    transmitBeep(C3, 200);
    transmitBeep(E3, 200);
    _delay_ms(200);
    transmitBeep(G3, 400);
    _delay_ms(500);
    transmitBeep(G2, 400);

    _delay_ms(2500);

  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
