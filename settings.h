/*
 * settings.h
 *
 * Created: 21.09.2016 10:43:49
 */ 


#pragma once

#include <Arduino.h>


#ifndef CHAOTIC
#define CHAOTIC
#endif // CHAOTIC

#ifndef NODEBUG
#define NODEBUG
#endif // NODEBUG

// total channels number
#define N_CHANNELS  5

// total amplitudes number
#define N_QUANT     2

#ifdef _VARIANT_ARDUINO_ZERO_
#define DOUBLYPIN   3
#define PIN_DAC     A0
#else
#define PIN_DAC     DAC0
#define DOUBLYPIN   40
#define DOUBLYPORT  PIOC
#define PINSHIFT    8
#endif
#define HALFWIDTHUS 2

#define ZEROSHIFT   2700

// #define INVERSE

#ifdef INVERSE
#define INVSETTING(x)    (4095 - (x))
#else
#define INVSETTING(x)    x
#endif

/*1 - linear, 2 - square, 3 - parabolic*/

#define SIGNTYPE    3

#if (SIGNTYPE == 1)

#define TYPICAL_US  2u

#elif (SIGNTYPE == 2)

#define TYPICAL_US  12u

#elif (SIGNTYPE == 3)

#define TYPICAL_US  1

#endif
