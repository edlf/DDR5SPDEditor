#ifndef UTILITIES_H
#define UTILITIES_H

namespace utilities {

unsigned short Crc16(unsigned char bytes[], unsigned int length);

unsigned short ConvertBytes(unsigned char lsb, unsigned char msb);

void Convert16bitUnsignedInteger(unsigned char& lsb, unsigned char& msb, unsigned short value);

unsigned short TimeToTicksDDR5(unsigned int time, unsigned int minCycleTime);

void SetCLSupportedDDR5(unsigned char clSupported[5], int cl, bool supported);

bool IsCLSupportedDDR5(unsigned char clSupported[5], int cl);

unsigned short ConvertByteToVoltageDDR5(unsigned char val);

unsigned char ConvertVoltageToByteDDR5(unsigned char voltage);

unsigned char SetByte(unsigned char bits, unsigned short bitNumber, bool value);

} // namespace utilities

#endif // UTILITIES_H
