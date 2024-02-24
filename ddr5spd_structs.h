#ifndef DDR5SPD_STRUCTS_H
#define DDR5SPD_STRUCTS_H

#include <stddef.h>

namespace ddr5_structs {

constexpr size_t eepromSize = 1024;
constexpr size_t partNumberSize = 30;
constexpr size_t jedecBlockSize = 0x200;

// XMP 3.0
constexpr size_t XMPHeaderSize = 0x40;
constexpr size_t XMPProfileSize = 0x40;
constexpr size_t maxXmpProfileName = 15;
constexpr unsigned int IntelDynamicMemoryBoostBit = 0;
constexpr unsigned int RealTimeMemoryFrequencyOCBit = 1 ;
constexpr char XMPHeaderMagic[] = { 0x0C, 0x4A };
constexpr unsigned int xmpProfile1EnableBit = 0;
constexpr unsigned int xmpProfile2EnableBit = 1;
constexpr unsigned int xmpProfile3EnableBit = 2;

enum class FormFactor
{
    Reserved,
    RDIMM,
    UDIMM,
    SODIMM,
    LRDIMM,
    CUDIMM,
    CSODIMM,
    MRDIMM,
    CAMM2,
    Reserved_9,
    DDIMM,
    Solder_down,
    Reserved_12,
    Reserved_13,
    Reserved_14,
    Reserved_15,
    Count
};

enum class Densities
{
    _0Gb,
    _4Gb,
    _8Gb,
    _12Gb,
    _16Gb,
    _24Gb,
    _32Gb,
    _48Gb,
    _64Gb,
    Count
};

enum class CommandRate
{
    Undefined,
    _1n,
    _2n,
    _3n
};

#pragma pack(push,1)
struct AuxDevice {
    unsigned char manufacturer[2];
    unsigned char deviceType;
    unsigned char revision;
};

struct CAS {
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;
    unsigned char byte5;
};

struct XMP_HeaderStruct {
    unsigned char magic1;
    unsigned char magic2;
    unsigned char version;
    unsigned char profileEnBits;

    unsigned char unknown_04; // 0x00
    unsigned char pmicManufacturerId[2];

    unsigned char unknown_07; // 0x01
    unsigned char unknown_08; // 0x03
    unsigned char unknown_09; // 0x12
    unsigned char unknown_0A; // 0x00
    unsigned char unknown_0B; // 0x00
    unsigned char unknown_0C; // 0x00
    unsigned char unknown_0D; // 0x00

    char profileName1[maxXmpProfileName];
    unsigned char spacer1;
    char profileName2[maxXmpProfileName];
    unsigned char spacer2;
    char profileName3[maxXmpProfileName];
    unsigned char spacer3;
    unsigned char checksum[2];
};

struct XMP_ProfileStruct {
    unsigned char vpp;
    unsigned char vdd;
    unsigned char vddq;
    unsigned char unknown_03;
    unsigned char vmemctrl;
    unsigned char minCycleTime[2];
    CAS clSupported;
    unsigned char unkown_0A;
    unsigned char tAA[2];
    unsigned char tRCD[2];
    unsigned char tRP[2];
    unsigned char tRAS[2];
    unsigned char tRC[2];
    unsigned char tWR[2];
    unsigned char tRFC1[2];
    unsigned char tRFC2[2];
    unsigned char tRFC[2];
    unsigned char tRRD_L[2];
    unsigned char tRRD_L_lowerLimit;
    unsigned char tCCD_L_WR[2];
    unsigned char tCCD_L_WR_lowerLimit;
    unsigned char tCCD_L_WR2[2];
    unsigned char tCCD_L_WR2_lowerLimit;
    unsigned char tCCD_L_WTR[2];
    unsigned char tCCD_L_WTR_lowerLimit;
    unsigned char tCCD_S_WTR[2];
    unsigned char tCCD_S_WTR_lowerLimit;
    unsigned char tCCD_L[2];
    unsigned char tCCD_L_lowerLimit;
    unsigned char tRTP[2];
    unsigned char tRTP_lowerLimit;
    unsigned char tFAW[2];
    unsigned char tFAW_lowerLimit;
    unsigned char unknown_07;
    unsigned char unknown_08;
    unsigned char unknown_09;
    unsigned char unknown_0A;
    unsigned char memory_boost_realtime_training;
    unsigned char commandRate;
    unsigned char unknown_0D;

    // Byte 0x3E-0x4F
    unsigned char checksum[2];
};

struct XMP_Struct {
    XMP_HeaderStruct header;
    XMP_ProfileStruct profile1;
    XMP_ProfileStruct profile2;
    XMP_ProfileStruct profile3;
    XMP_ProfileStruct user_profile1;
    XMP_ProfileStruct user_profile2;
};

struct SPD_Struct {
    // Start General configuration (0-127, 0x00-0x7F, Block 0,1)
    // Byte 0 to 3 Header/Type
    unsigned char bytesUsed;
    unsigned char revision_BaseConfig;
    unsigned char memoryType; // 12 = DDR5
    unsigned char moduleType; // 0x02 = Unbuffered DIMM, 0x03 = SO-DIMM, 0x04=LRDIMM (only bits 3-0 are used)
    // Byte 4-7 First Density/Package
    unsigned char firstDensityPackage;
    unsigned char firstAddressing;
    unsigned char firstIOWitdth;
    unsigned char firstBankGroups;
    // Byte 8-11 Second Density/Package
    unsigned char secondDensityPackage;
    unsigned char secondAddressing;
    unsigned char secondIOWitdth;
    unsigned char secondBankGroups;
    // Byte 12
    unsigned char sdramBL32;
    unsigned char sdramDutyCycle;
    unsigned char sdramFaultHandling;
    unsigned char reserved_15;
    // Byte 16-18 (Voltages, 1.1v)
    unsigned char voltageVDD;  // 0x00 -> 1.1v
    unsigned char voltageVDDQ; // 0x00 -> 1.1v
    unsigned char voltageVPP;  // 0x00 -> 1.1v
    // Byte 19
    unsigned char sdramTimming; // Should be 0x00 for JEDEC standard timmings
    // Byte 20-21
    unsigned char minCycleTime[2];
    // Byte 22-23
    unsigned char maxCycleTime[2];
    // Byte 24-28 Cas Latencies supported
    CAS clSupported;
    unsigned char reserved_29;
    // Byte 30-31 tAA
    unsigned char tAA[2];
    // Byte 32-33 tRCD
    unsigned char tRCD[2];
    // Byte 34-35 tRP
    unsigned char tRP[2];
    // Byte 36-37 tRAS
    unsigned char tRAS[2];
    // Byte 38-39 tRC
    unsigned char tRC[2];
    // Byte 40-41 tWR
    unsigned char tWR[2];

    // Same logical bank
    // Byte 42-43 tRFC1 (Normal Refresh Recovery Time)
    unsigned char tRFC1_slr[2];
    // Byte 44-45 tRFC2 (Fine Granularity Refresh Recovery Time)
    unsigned char tRFC2_slr[2];
    // Byte 46-47 tRFCsb (Same Bank Refresh Recovery Time)
    unsigned char tRFCsb_slr[2];

    // Different logical bank
    // Byte 48-49 tRFC1 (Normal Refresh Recovery Time)
    unsigned char tRFC1_dlr[2];
    // Byte 50-51 tRFC2 (Fine Granularity Refresh Recovery Time)
    unsigned char tRFC2_dlr[2];
    // Byte 52-53 tRFCsb (Same Bank Refresh Recovery Time)
    unsigned char tRFCsb_dlr[2];

    // Byte 54-57 SDRAM Refresh Management
    unsigned char refreshManagementFirst[2];
    unsigned char refreshManagementSecond[2];

    // Byte 58-61 Adaptive Refresh Management Level A
    unsigned char adaptiveRefreshManagementAFirst[2];
    unsigned char adaptiveRefreshManagementASecond[2];

    // Byte 62-65 Adaptive Refresh Management Level B
    unsigned char adaptiveRefreshManagementBFirst[2];
    unsigned char adaptiveRefreshManagementBSecond[2];

    // Byte 66-69 Adaptive Refresh Management Level C
    unsigned char adaptiveRefreshManagementCFirst[2];
    unsigned char adaptiveRefreshManagementCSecond[2];

    // Byte 70-72 Activate to Activate Command Delay for Same Bank Group
    unsigned char tRRD_L[2];
    unsigned char tRRD_L_lowerLimit;

    // Byte 73-75 Read to Read Command Delay for Same Bank Group
    unsigned char tCCD_L[2];
    unsigned char tCCD_L_lowerLimit;

    // Byte 76-78 Write to Write Command Delay for Same Bank Group
    unsigned char tCCD_L_WR[2];
    unsigned char tCCD_L_WR_lowerLimit;

    // Byte 79-81 Write to Write Command Delay for Same Bank Group, Second Write not RMW
    unsigned char tCCD_L_WR2[2];
    unsigned char tCCD_L_WR2_lowerLimit;

    // Byte 82-84 Four Activate Window
    unsigned char tFAW[2];
    unsigned char tFAW_lowerLimit;

    // Byte 85-87 Write to Read Command Delay for Same Bank Group
    unsigned char tCCD_L_WTR[2];
    unsigned char tCCD_L_WTR_lowerLimit;

    // Byte 88-90 Write to Read Command Delay for Different Bank Group
    unsigned char tCCD_S_WTR[2];
    unsigned char tCCD_S_WTR_lowerLimit;

    // Byte 91-93 Read to Precharge Command Delay
    unsigned char tRTP[2];
    unsigned char tRTP_lowerLimit;

    // Byte 94-96 Read to Read Command Delay for Different Bank in Same Bank
    unsigned char tCCD_M[2];
    unsigned char tCCD_M_lowerLimit;

    // Byte 97-99 Write to Write Command Delay for Different Bank in Same Bank Group
    unsigned char tCCD_M_WR[2];
    unsigned char tCCD_M_WR_lowerLimit;

    // Byte 100-102 Write to Read Command Delay for Same Bank Group
    unsigned char tCCD_M_WTR[2];
    unsigned char tCCD_M_WTR_lowerLimit;

    // Byte 103-127 Reserved
    unsigned char reserved_103_127[25];

    // End General configuration


    // Block 2 - Reserved for future use
    // Reserved (128-191, 0x80-0xBF)
    unsigned char reserved_128_191[64];


    // Block 3 - Common Module Parameters/Standard Module Parameters
    // Byte 192 SPD Revision for SPD bytes 192~447
    unsigned char revision_CommonBytes;
    // Byte 193
    unsigned char hashingSequence;

    // Byte 194-197 SPD
    AuxDevice spdHub;

    // Byte 198-201 PMIC 0, 202-205 PMIC 1, 206-209 PMIC 2
    AuxDevice pmic0;
    AuxDevice pmic1;
    AuxDevice pmic2;

    // Byte 210-213 Thermal Sensor
    AuxDevice thermalSensor;

    // Byte 214-229 Reserved
    unsigned char reserved_214_229[16];

    // Byte 230
    unsigned char moduleHeight;
    // Byte 231
    unsigned char moduleMaxThickness;
    // Byte 232
    unsigned char refRawCard;
    // Byte 233
    unsigned char dimmAttributes;
    // Byte 234
    unsigned char moduleOrganization;
    // Byte 235
    unsigned char memoryChannelBusWidth;

    // Byte 236-239 Reserved
    unsigned char reserved_236_239[4];

    // Ending of block 3 + block 4/5/6

    // Byte 240-447 - Not used for regular DDR5
    unsigned char reserved_240_447[208];

    // ------------------------ Block 7 ------------------------
    // Reserved (448-509, 0x1C0-0x1FD)
    unsigned char reserved_448_509[62];

    // Byte 510-511 Checksum (for bytes 0-509)
    unsigned char checksum[2];
    // ---------------------- End block 7 ----------------------

    // Block 8 - Manufacturing information
    // Byte 512
    unsigned char moduleManufacturer[2]; // Mandatory
    // Byte 514
    unsigned char manufactureLocation; // Mandatory
    // Byte 515-516
    char manufactureDate[2]; // Mandatory
    // Bytes 517-520
    unsigned char serialNumber[4]; // Mandatory
    // Bytes 521-550
    char modulePartnumber[partNumberSize]; // Mandatory
    // Byte 551
    unsigned char moduleRevision;
    // Byte 552-553 DRAM Manufacturer ID Code
    unsigned char dramManufacturer[2]; // Mandatory
    // Byte 554 DRAM stepping
    unsigned char dramStepping;

    // Block 9 - Manufacturing information

    // Bytes 555~639 (0x22B~27F): Manufacturer’s Specific Data
    unsigned char reserved_555_639[640 - 555];

    // End User bits (XMP/EXPO) 0x280 (1024 - 640)
    XMP_Struct xmpBlock;
};
#pragma pack(pop)

static_assert(sizeof(SPD_Struct) == 0x400, "SPD struct size error");
static_assert(sizeof(XMP_HeaderStruct) == XMPHeaderSize, "XMP Header has to be 64 bytes in size");
static_assert(sizeof(XMP_ProfileStruct) == XMPProfileSize, "XMP Profile has to be 64 bytes in size");
static_assert(sizeof(XMP_Struct) == (sizeof(XMP_HeaderStruct) + 5*sizeof(XMP_ProfileStruct)), "XMP Block size is incorrect");

}; // namespace

#endif // DDR5SPD_STRUCTS_H
