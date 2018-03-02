
#include "signalgen.h"


#if ((SIGNTYPE == 2) || (SIGNTYPE == 3))
const float sqrt_values[] = { 0.0, 1.0, 1.4142, 1.7321, 2.0, 2.2361, 2.4495, 2.6458, 2.8284, 3.0 };
#endif

static int dist_us = 1, width = 10;
static uint8_t amp_compatibility = 3; // N_CHANNELS;

void signalgen(const uint8_t *amp)
{
    if (amp == NULL)    {amp = &amp_compatibility;}
#ifdef _VARIANT_ARDUINO_ZERO_
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
#else
    PIOC->PIO_SODR = (1 << PINSHIFT);
    PIOC->PIO_SODR = (1 << 2);
#endif

#if (SIGNTYPE == 1)

    for (uint8_t i = 1; i <= (*amp); i++)
    {
        PIOC->PIO_SODR = (1 << (i + 1)); // signal to comparators
        dacc_write_conversion_data(DACC_INTERFACE, INVSETTING((4000 * i) / N_QUANT + 10)); // signal to ADC

#if TYPICAL_US
        delayMicroseconds(TYPICAL_US);
#endif // TYPICAL_US
    }
    for (int8_t i = (*amp); i >= 1; i--)
    {
        dacc_write_conversion_data(DACC_INTERFACE, INVSETTING((4000 * i) / N_QUANT + 10)); // signal to ADC
        PIOC->PIO_CODR = (1 << (i + 1)); // signal to comparators

#if TYPICAL_US
        delayMicroseconds(TYPICAL_US);
#endif // TYPICAL_US
    }

#elif (SIGNTYPE == 2)

    dacc_write_conversion_data(DACC_INTERFACE, INVSETTING((4000 * (*amp)) / N_QUANT + 10)); // signal to ADC
    delayMicroseconds((uint)(TYPICAL_US * sqrt_values[(*amp)]));
    dacc_write_conversion_data(DACC_INTERFACE, 0); // signal to ADC

#elif (SIGNTYPE == 3)

    int i, n = (int)(8 * sqrt_values[(*amp)]); // for linear scattering
    for (i = 0; i <= n; i++)
    {
#ifdef _VARIANT_ARDUINO_ZERO_
        // analogWrite(A0, INVSETTING(42 * (n*i - (i*i)) + ZEROSHIFT));
        dacc_write_conversion_data(&A0, INVSETTING((80 / N_QUANT) * (n*i - (i*i)) + ZEROSHIFT));
#else
        dacc_write_conversion_data(DACC_INTERFACE, INVSETTING(((80/N_QUANT)*(n*i - (i*i)) + ZEROSHIFT))); // signal to ADC
#endif
#if TYPICAL_US
        delayMicroseconds(TYPICAL_US);
#endif // TYPICAL_US
    }

#else

#pragma message ("no signal type chosen, nothing will be generated!")

#endif // SIGNTYPE

#ifdef _VARIANT_ARDUINO_ZERO_
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
#else
    PIOC->PIO_CODR = (1 << PINSHIFT);
    PIOC->PIO_CODR = (1 << 2);
#endif

#ifdef _VARIANT_ARDUINO_ZERO_
    analogWrite(A0, INVSETTING(0));
#else
    dacc_write_conversion_data(DACC_INTERFACE, INVSETTING(ZEROSHIFT));
#endif
    delayMicroseconds(dist_us);
}

