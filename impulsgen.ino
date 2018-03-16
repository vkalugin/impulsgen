/*
 * Name:    impulsgen.ino
 * Brief:   Generates simple impulses which can be used for another board.
 */

#include "signalgen.h"


const uint8_t channel[] = { 34, 35, 36, 37, 38, 39, 40, 41 };
uint8_t amp;

void setup()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        pinMode(channel[i], OUTPUT);
        digitalWrite(channel[i], LOW);
    }

    analogWriteResolution(12);
    analogWrite(PIN_DAC, 0);

#ifdef CHAOTIC
#ifdef _VARIANT_ARDUINO_ZERO_
    randomSeed(analogRead(A0));
#else
    randomSeed(analogRead(ADC0));
#endif // _VARIANT_ARDUINO_ZERO_
#endif // CHAOTIC

    pinMode(DOUBLYPIN, OUTPUT);
    digitalWrite(DOUBLYPIN, LOW);
    
    while (true)
    {
#ifdef CHAOTIC
        amp = random(1, N_QUANT + 1);
#endif // CHAOTIC

        signalgen(&amp);
    }
    
    exit(0);
}

void loop()
{
    exit(-1); // this shouldn't be normally
}
