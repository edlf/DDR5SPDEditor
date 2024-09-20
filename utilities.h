#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include "ddr5spd_structs.h"

namespace utilities {

unsigned short Crc16(unsigned char bytes[], unsigned int length);

unsigned short TimeToTicksDDR5(const unsigned int time, const unsigned int minCycleTime);

void SetCLSupportedDDR5(ddr5_structs::CAS&, unsigned short cl, bool supported);

bool IsCLSupportedDDR5(const ddr5_structs::CAS&, unsigned short cl);

unsigned short ConvertByteToVoltageDDR5(unsigned char val);

unsigned char ConvertVoltageToByteDDR5(unsigned char voltage);

void SetBit(unsigned char& bits, const unsigned short bitNumber, const bool value);

bool GetBit(unsigned char bits, unsigned short bitNumber);

void SetCString(const std::string value, const size_t maxLength, char* destination);

unsigned short convert_date_byte(const unsigned char);

unsigned char convert_to_date_byte(const unsigned short);

} // namespace utilities

#endif // UTILITIES_H
