#include "utilities.h"

#include <string>
#include <sstream>
#include <format>

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

unsigned short TimeToTicksDDR5(const unsigned int time, const unsigned int minCycleTime) {
    if (minCycleTime == 0) {
        return 0;
    }

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

void SetCLSupportedDDR5(ddr5_structs::CAS& clSupported, unsigned short cl, bool supported)
{
    // All valid CAS latencies are even numbers between 20 and 98
    if ((cl < 20) || (cl > 98) || (cl % 2 != 0))
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
            clSupported.byte1 |= mask[index];
        }
        else
        {
            clSupported.byte1 &= ~mask[index];
        }
    }
    else if (cl >= 36 && cl <= 50)
    {
        int index = bit - 8;
        if (supported)
        {
            clSupported.byte2 |= mask[index];
        }
        else
        {
            clSupported.byte2 &= ~mask[index];
        }
    }
    else if (cl >= 52 && cl <= 66)
    {
        int index = bit - 16;
        if (supported)
        {
            clSupported.byte3 |= mask[index];
        }
        else
        {
            clSupported.byte3 &= ~mask[index];
        }
    }
    else if (cl >= 68 && cl <= 82)
    {
        int index = bit - 24;
        if (supported)
        {
            clSupported.byte4 |= mask[index];
        }
        else
        {
            clSupported.byte4 &= ~mask[index];
        }
    }
    else if (cl >= 84 && cl <= 98)
    {
        int index = bit - 32;
        if (supported)
        {
            clSupported.byte5 |= mask[index];
        }
        else
        {
            clSupported.byte5 &= ~mask[index];
        }
    }
}

bool IsCLSupportedDDR5(const ddr5_structs::CAS& clSupported, unsigned short cl)
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
        return (clSupported.byte1 & mask[index]) == mask[index];
    }
    else if (cl >= 36 && cl <= 50)
    {
        int index = bit - 8;
        return (clSupported.byte2 & mask[index]) == mask[index];
    }
    else if (cl >= 52 && cl <= 66)
    {
        int index = bit - 16;
        return (clSupported.byte3 & mask[index]) == mask[index];
    }
    else if (cl >= 68 && cl <= 82)
    {
        int index = bit - 24;
        return (clSupported.byte4 & mask[index]) == mask[index];
    }
    else if (cl >= 84 && cl <= 98)
    {
        int index = bit - 32;
        return (clSupported.byte5 & mask[index]) == mask[index];
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

void SetBit(unsigned char& bits, const unsigned short bitNumber, const bool value)
{
    if (value)
    {
        bits |= (1 << bitNumber);
    }
    else
    {
        bits &= (0xFF ^ (1 << bitNumber));
    }
}

bool GetBit(unsigned char bits, unsigned short bitNumber) {
    return ((bits & (1 << bitNumber)) != 0);
}

void SetCString(const std::string value, const size_t maxLength, char* destination) {
    std::string str = value.substr(0, std::min(maxLength, value.size()));

    for (int i = 0; i < str.size(); ++i)
    {
        destination[i] = str[i];
    }
    for (int i = str.size(); i < maxLength; ++i)
    {
        destination[i] = 0;
    }
}

unsigned short convert_date_byte(const unsigned char byte)
{
    std::string temp = std::format("{:x}", byte);
    return stoi(temp);
}

unsigned char convert_to_date_byte(const unsigned short value) {
    std::string temp = std::to_string(value);
    return std::stoul(temp.c_str(), nullptr, 16);
}

} // namespace utilities
