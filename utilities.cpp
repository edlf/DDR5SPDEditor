#include "utilities.h"

namespace utilities {

unsigned short Crc16(unsigned char bytes[], unsigned int length) {
    unsigned int crc = 0;

    for (unsigned int i = 0; i < length; i++) {
        crc ^= bytes[i] << 8;
        for (unsigned int j = 0; j < 8; j++) {
            if ((crc & 0x8000) == 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc <<= 1;
            }
        }
    }

    return (crc & 0xFFFF);
}

unsigned short ConvertBytes(unsigned char lsb, unsigned char msb) {
    return (msb << 8) + lsb;
}

void Convert16bitUnsignedInteger(unsigned char& lsb, unsigned char& msb, unsigned short value) {
    lsb = static_cast<unsigned char>(value & 0xff);
    msb = static_cast<unsigned char>((value & 0xff00) >> 8);
}

unsigned short TimeToTicksDDR5(const unsigned int time, const unsigned int minCycleTime) {
    // 0.30% per the rounding algorithm per JESD400-5B
    constexpr unsigned int correctionFactor = 3;

    // Apply correction factor, scaled by 1000
    unsigned int temp = time * (1000 - correctionFactor);
    // Initial nCK calculation, scaled by 1000
    float tempNck = temp / minCycleTime;
    // Add 1, scaled by 1000, to effectively round up
    tempNck += 1000.0;
    // Round down to next integer
    return static_cast<unsigned short>(tempNck / 1000);
}

void SetCLSupportedDDR5(unsigned char clSupported[5], int cl, bool supported)
{
    // All valid CAS latencies are even numbers between 20 and 98
    if (cl < 20 || cl > 98 || (cl % 2 != 0))
    {
        return;
    }

    unsigned int mask[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

    const int offset = 20;
    int bit = (cl - offset) / 2;

    if (cl >= 20 && cl <= 34)
    {
        int index = bit;
        if (supported)
        {
            clSupported[0] |= mask[index];
        }
        else
        {
            clSupported[0] &= ~mask[index];
        }
    }
    else if (cl >= 36 && cl <= 50)
    {
        int index = bit - 8;
        if (supported)
        {
            clSupported[1] |= mask[index];
        }
        else
        {
            clSupported[1] &= ~mask[index];
        }
    }
    else if (cl >= 52 && cl <= 66)
    {
        int index = bit - 16;
        if (supported)
        {
            clSupported[2] |= mask[index];
        }
        else
        {
            clSupported[2] &= ~mask[index];
        }
    }
    else if (cl >= 68 && cl <= 82)
    {
        int index = bit - 24;
        if (supported)
        {
            clSupported[3] |= mask[index];
        }
        else
        {
            clSupported[3] &= ~mask[index];
        }
    }
    else if (cl >= 84 && cl <= 98)
    {
        int index = bit - 32;
        if (supported)
        {
            clSupported[4] |= mask[index];
        }
        else
        {
            clSupported[4] &= ~mask[index];
        }
    }
}

bool IsCLSupportedDDR5(unsigned char clSupported[5], int cl)
{
    unsigned int mask[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

    // All valid CAS latencies are even numbers between 20 and 98
    if (cl < 20 || cl > 98 || (cl % 2 != 0))
    {
        return false;
    }

    const int offset = 20;
    int bit = (cl - offset) / 2;

    if (cl >= 20 && cl <= 34)
    {
        int index = bit;
        return (clSupported[0] & mask[index]) == mask[index];
    }
    else if (cl >= 36 && cl <= 50)
    {
        int index = bit - 8;
        return (clSupported[1] & mask[index]) == mask[index];
    }
    else if (cl >= 52 && cl <= 66)
    {
        int index = bit - 16;
        return (clSupported[2] & mask[index]) == mask[index];
    }
    else if (cl >= 68 && cl <= 82)
    {
        int index = bit - 24;
        return (clSupported[3] & mask[index]) == mask[index];
    }
    else if (cl >= 84 && cl <= 98)
    {
        int index = bit - 32;
        return (clSupported[4] & mask[index]) == mask[index];
    }

    // Should never reach this point
    return false;
}

unsigned short ConvertByteToVoltageDDR5(unsigned char val)
{
    unsigned short ones = (val >> 5);
    unsigned short hundredths = (val & 0x1F);

    return (ones * 100 + hundredths * 5);
}

unsigned char ConvertVoltageToByteDDR5(unsigned char voltage)
{
    unsigned short ones = (voltage / 100);
    unsigned short hundredths = (voltage % 100);

    return ((ones << 5) + (hundredths / 5));
}

unsigned char SetByte(unsigned char bits, unsigned short bitNumber, bool value)
{
    if (value)
    {
        bits |= (1 << bitNumber);
    }
    else
    {
        bits &= (0xFF ^ (1 << bitNumber));
    }

    return bits;
}

} // namespace utilities
