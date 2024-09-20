#ifndef DDR5SPD_STRUCTS_H
#define DDR5SPD_STRUCTS_H

#include <array>
#include <stddef.h>
#include <type_traits>
#include <bit>

namespace ddr5_structs {

// JEDEC
constexpr size_t eepromSize = 0x400;
constexpr size_t partNumberSize = 30;
constexpr size_t jedecBlockSize = 0x200;

// XMP 3.0
constexpr size_t XMPHeaderSize = 0x40;
constexpr size_t XMPProfileSize = 0x40;
constexpr size_t maxXmpProfileName = 16;

constexpr char XMPHeaderMagic[] = { 0x0C, 0x4A };
constexpr char XMPHeaderVersion = 0x30;
constexpr unsigned int xmpProfile1EnableBit = 0;
constexpr unsigned int xmpProfile2EnableBit = 1;
constexpr unsigned int xmpProfile3EnableBit = 2;

constexpr unsigned int IntelDynamicMemoryBoostBit = 0;
constexpr unsigned int RealTimeMemoryFrequencyOCBit = 1;

// EXPO
constexpr size_t EXPOHeaderSize = 0xA;
constexpr size_t EXPOSize = 0x80;
constexpr size_t EXPOProfileSize = 0x28;
constexpr char EXPOHeaderMagic[] = { 0x45, 0x58, 0x50, 0x4F };
constexpr char EXPORevision = 0x10;
constexpr unsigned int expoProfile1EnableBit = 0;
constexpr unsigned int expoProfile2EnableBit = 4;
// Unkown bits, always seem enabled when the respective profile is enabled
constexpr unsigned int expoProfile1UnkBit = 1;
constexpr unsigned int expoProfile2UnkBit = 5;

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
    Reserved_15
};

enum class Density
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

enum class OperatingTemperatureRange
{
    A1T,
    A2T,
    A3T,
    IT,
    ST,
    ET,
    RT,
    NT,
    XT
};

static constexpr std::array<Density, 9> densityMap {
    Density::_0Gb,
    Density::_4Gb,
    Density::_8Gb,
    Density::_12Gb,
    Density::_16Gb,
    Density::_24Gb,
    Density::_32Gb,
    Density::_48Gb,
    Density::_64Gb
};

static constexpr std::array<CommandRate, 4> commandRateMap {
    CommandRate::Undefined,
    CommandRate::_1n,
    CommandRate::_2n,
    CommandRate::_3n
};

static constexpr std::array<FormFactor, 16> formFactorMap {
    FormFactor::Reserved,
    FormFactor::RDIMM,
    FormFactor::UDIMM,
    FormFactor::SODIMM,
    FormFactor::LRDIMM,
    FormFactor::CUDIMM,
    FormFactor::CSODIMM,
    FormFactor::MRDIMM,
    FormFactor::CAMM2,
    FormFactor::Reserved_9,
    FormFactor::DDIMM,
    FormFactor::Solder_down,
    FormFactor::Reserved_12,
    FormFactor::Reserved_13,
    FormFactor::Reserved_14,
    FormFactor::Reserved_15
};

static constexpr std::array<OperatingTemperatureRange, 9> operatingTemperatureRangeMap {
    OperatingTemperatureRange::A1T,
    OperatingTemperatureRange::A2T,
    OperatingTemperatureRange::A3T,
    OperatingTemperatureRange::IT,
    OperatingTemperatureRange::ST,
    OperatingTemperatureRange::ET,
    OperatingTemperatureRange::RT,
    OperatingTemperatureRange::NT,
    OperatingTemperatureRange::XT
};

static constexpr std::array<unsigned short, 4> bankGroupsBitsMap{ 1, 2, 4, 8 };
static constexpr std::array<unsigned short, 3> banksPerBankGroupBitsMap{ 1, 2, 4 };
static constexpr std::array<unsigned short, 2> columnAddressBitsMap{ 10, 11 };
static constexpr std::array<unsigned short, 3> rowAddressBitsMap{ 16, 17, 18 };
static constexpr std::array<unsigned short, 4> deviceWidthMap{ 4, 8, 16, 32 };

#pragma pack(push,1)
struct AuxDevice {
    unsigned short manufacturer;
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
    char profileName2[maxXmpProfileName];
    char profileName3[maxXmpProfileName];
    unsigned short checksum;
};

struct XMP_ProfileStruct {
    unsigned char vpp;
    unsigned char vdd;
    unsigned char vddq;
    unsigned char unknown_03;
    unsigned char vmemctrl;
    unsigned short minCycleTime;
    CAS clSupported;
    unsigned char unkown_0A;
    unsigned short tAA;
    unsigned short tRCD;
    unsigned short tRP;
    unsigned short tRAS;
    unsigned short tRC;
    unsigned short tWR;
    unsigned short tRFC1;
    unsigned short tRFC2;
    unsigned short tRFC;
    unsigned short tRRD_L;
    unsigned char tRRD_L_lowerLimit;
    unsigned short tCCD_L_WR;
    unsigned char tCCD_L_WR_lowerLimit;
    unsigned short tCCD_L_WR2;
    unsigned char tCCD_L_WR2_lowerLimit;
    unsigned short tCCD_L_WTR;
    unsigned char tCCD_L_WTR_lowerLimit;
    unsigned short tCCD_S_WTR;
    unsigned char tCCD_S_WTR_lowerLimit;
    unsigned short tCCD_L;
    unsigned char tCCD_L_lowerLimit;
    unsigned short tRTP;
    unsigned char tRTP_lowerLimit;
    unsigned short tFAW;
    unsigned char tFAW_lowerLimit;
    unsigned char unknown_07;
    unsigned char unknown_08;
    unsigned char unknown_09;
    unsigned char unknown_0A;
    unsigned char memory_boost_realtime_training;
    unsigned char commandRate;
    unsigned char unknown_0D;

    // Byte 0x3E-0x4F
    unsigned short checksum;
};

struct XMP_Struct {
    XMP_HeaderStruct header;
    XMP_ProfileStruct profile1;
    XMP_ProfileStruct profile2;
    XMP_ProfileStruct profile3;
    XMP_ProfileStruct user_profile1;
    XMP_ProfileStruct user_profile2;
};

struct EXPO_HeaderStruct {
    unsigned char magic[4];
    unsigned char revision; // 0x10
    unsigned char profileEnableBits;
    unsigned char profileEnableBits2;
    unsigned char zero_7;
    unsigned char zero_8;
    unsigned char zero_9;
};

struct EXPO_ProfileStruct {
    unsigned char vdd;
    unsigned char vddq;
    unsigned char vpp;
    unsigned char unk1;
    unsigned short minCycleTime;
    unsigned short tAA;
    unsigned short tRCD;
    unsigned short tRP;
    unsigned short tRAS;
    unsigned short tRC;
    unsigned short tWR;
    unsigned short tRFC1;
    unsigned short tRFC2;
    unsigned short tRFC;
    unsigned short tRRD_L;
    unsigned short tCCD_L;
    unsigned short tCCD_L_WR;
    unsigned short tCCD_L_WR2;
    unsigned short tFAW;
    unsigned short tCCD_L_WTR;
    unsigned short tCCD_S_WTR;
    unsigned short tRTP;
};

struct EXPO_Struct {
    EXPO_HeaderStruct header;
    EXPO_ProfileStruct profile1;
    EXPO_ProfileStruct profile2;

    // TODO: Figure out second profile + voltages
    unsigned char filler[0x24];

    // Byte 0x7E-0x7F
    unsigned short checksum;
};

// Hybrid XMP3/EXPO
struct XMP_EXPO_Hybrid_Struct {
    XMP_HeaderStruct header;
    XMP_ProfileStruct profile1;
    XMP_ProfileStruct profile2;
    EXPO_Struct expo_struct;
    XMP_ProfileStruct user_profile2;
};

union XMP_EXPO_Union {
    XMP_EXPO_Hybrid_Struct hybrid;
    XMP_Struct xmpOnly;
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
    unsigned short minCycleTime;
    // Byte 22-23
    unsigned short maxCycleTime;
    // Byte 24-28 Cas Latencies supported
    CAS clSupported;
    unsigned char reserved_29;
    // Byte 30-31 tAA
    unsigned short tAA;
    // Byte 32-33 tRCD
    unsigned short tRCD;
    // Byte 34-35 tRP
    unsigned short tRP;
    // Byte 36-37 tRAS
    unsigned short tRAS;
    // Byte 38-39 tRC
    unsigned short tRC;
    // Byte 40-41 tWR
    unsigned short tWR;

    // Same logical bank
    // Byte 42-43 tRFC1 (Normal Refresh Recovery Time)
    unsigned short tRFC1_slr;
    // Byte 44-45 tRFC2 (Fine Granularity Refresh Recovery Time)
    unsigned short tRFC2_slr;
    // Byte 46-47 tRFCsb (Same Bank Refresh Recovery Time)
    unsigned short tRFCsb_slr;

    // Different logical bank
    // Byte 48-49 tRFC1 (Normal Refresh Recovery Time)
    unsigned short tRFC1_dlr;
    // Byte 50-51 tRFC2 (Fine Granularity Refresh Recovery Time)
    unsigned short tRFC2_dlr;
    // Byte 52-53 tRFCsb (Same Bank Refresh Recovery Time)
    unsigned short tRFCsb_dlr;

    // Byte 54-57 SDRAM Refresh Management
    unsigned short refreshManagementFirst;
    unsigned short refreshManagementSecond;

    // Byte 58-61 Adaptive Refresh Management Level A
    unsigned short adaptiveRefreshManagementAFirst;
    unsigned short adaptiveRefreshManagementASecond;

    // Byte 62-65 Adaptive Refresh Management Level B
    unsigned short adaptiveRefreshManagementBFirst;
    unsigned short adaptiveRefreshManagementBSecond;

    // Byte 66-69 Adaptive Refresh Management Level C
    unsigned short adaptiveRefreshManagementCFirst;
    unsigned short adaptiveRefreshManagementCSecond;

    // Byte 70-72 Activate to Activate Command Delay for Same Bank Group
    unsigned short tRRD_L;
    unsigned char tRRD_L_lowerLimit;

    // Byte 73-75 Read to Read Command Delay for Same Bank Group
    unsigned short tCCD_L;
    unsigned char tCCD_L_lowerLimit;

    // Byte 76-78 Write to Write Command Delay for Same Bank Group
    unsigned short tCCD_L_WR;
    unsigned char tCCD_L_WR_lowerLimit;

    // Byte 79-81 Write to Write Command Delay for Same Bank Group, Second Write not RMW
    unsigned short tCCD_L_WR2;
    unsigned char tCCD_L_WR2_lowerLimit;

    // Byte 82-84 Four Activate Window
    unsigned short tFAW;
    unsigned char tFAW_lowerLimit;

    // Byte 85-87 Write to Read Command Delay for Same Bank Group
    unsigned short tCCD_L_WTR;
    unsigned char tCCD_L_WTR_lowerLimit;

    // Byte 88-90 Write to Read Command Delay for Different Bank Group
    unsigned short tCCD_S_WTR;
    unsigned char tCCD_S_WTR_lowerLimit;

    // Byte 91-93 Read to Precharge Command Delay
    unsigned short tRTP;
    unsigned char tRTP_lowerLimit;

    // Byte 94-96 Read to Read Command Delay for Different Bank in Same Bank
    unsigned short tCCD_M;
    unsigned char tCCD_M_lowerLimit;

    // Byte 97-99 Write to Write Command Delay for Different Bank in Same Bank Group
    unsigned short tCCD_M_WR;
    unsigned char tCCD_M_WR_lowerLimit;

    // Byte 100-102 Write to Read Command Delay for Same Bank Group
    unsigned short tCCD_M_WTR;
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
    unsigned short checksum;
    // ---------------------- End block 7 ----------------------

    // Block 8 - Manufacturing information
    // Byte 512
    unsigned short moduleManufacturer; // Mandatory
    // Byte 514
    unsigned char manufactureLocation; // Mandatory
    // Byte 515-516
    unsigned char manufactureDate[2]; // Mandatory
    // Bytes 517-520
    unsigned char serialNumber[4]; // Mandatory
    // Bytes 521-550
    char modulePartnumber[partNumberSize]; // Mandatory
    // Byte 551
    unsigned char moduleRevision;
    // Byte 552-553 DRAM Manufacturer ID Code
    unsigned short dramManufacturer; // Mandatory
    // Byte 554 DRAM stepping
    unsigned char dramStepping;

    // Block 9 - Manufacturing information

    // Bytes 555~639 (0x22B~27F): Manufacturer’s Specific Data
    unsigned char reserved_555_639[640 - 555];

    // End User bits (XMP/EXPO) 0x280 (1024 - 640)
    // XMP_Struct xmpBlock;
    XMP_EXPO_Union xmpExpoBlock;
};
#pragma pack(pop)

static_assert(std::endian::native == std::endian::little, "Little endian only"); // Requires C++20
static_assert(sizeof(unsigned short) == 0x2, "Unsigned shorts must be 16 bits!");
static_assert(sizeof(SPD_Struct) == eepromSize, "SPD struct size error");
static_assert(sizeof(XMP_HeaderStruct) == XMPHeaderSize, "XMP Header has to be 64 bytes in size");
static_assert(sizeof(XMP_ProfileStruct) == XMPProfileSize, "XMP Profile has to be 64 bytes in size");
static_assert(sizeof(XMP_Struct) == (sizeof(XMP_HeaderStruct) + 5*sizeof(XMP_ProfileStruct)), "XMP Block size is incorrect");
static_assert(sizeof(EXPO_Struct) == EXPOSize, "EXPO block has to be 128 bytes in size");
static_assert(sizeof(EXPO_ProfileStruct) == EXPOProfileSize, "EXPO profile has to be 40 bytes in size");

}; // namespace

#endif // DDR5SPD_STRUCTS_H
