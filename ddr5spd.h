#ifndef DDR5SPD_H
#define DDR5SPD_H

#include <QByteArray>
#include <cstddef>

class DDR5SPD
{

public:
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

    static const unsigned int eepromSize = 1024;
    static const unsigned int partNumberSize = 30;
    static const unsigned int maxXmpProfileName = 15;
    static constexpr unsigned char XMPHeaderMagic[2]{ 0x0C, 0x4A };
    static constexpr std::array<unsigned short, 4> bankGroupsBitsMap{ 1, 2, 4, 8 };
    static constexpr std::array<unsigned short, 3> banksPerBankGroupBitsMap{ 1, 2, 4 };
    static constexpr std::array<unsigned short, 2> columnAddressBitsMap{ 10, 11 };
    static constexpr std::array<unsigned short, 3> rowAddressBitsMap{ 16, 17, 18 };
    static constexpr std::array<unsigned short, 4> deviceWidthMap{ 4, 8, 16, 32 };

    #pragma pack(1)
    struct RawSPD
    {
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
        unsigned char clSupported[5];
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
        unsigned char spdManufacturer[2];
        unsigned char spdDeviceType;
        unsigned char spdRevision;

        // Byte 198-201 PMIC 0
        unsigned char pmic0Manufacturer[2];
        unsigned char pmic0DeviceType;
        unsigned char pmic0Revision;

        // Byte 202-205 PMIC 1
        unsigned char pmic1Manufacturer[2];
        unsigned char pmic1DeviceType;
        unsigned char pmic1Revision;

        // Byte 206-209 PMIC 2
        unsigned char pmic2Manufacturer[2];
        unsigned char pmic2DeviceType;
        unsigned char pmic2Revision;

        // Byte 210-213 Thermal Sensor
        unsigned char thermalSensorManufacturer[2];
        unsigned char thermalSensorDeviceType;
        unsigned char thermalSensorRevision;

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
        unsigned char moduleManufacturer[2];
        // Byte 514
        unsigned char manufactureLocation;
        // Byte 515-516
        unsigned char manufactureDate[2];
        // Bytes 517-520
        unsigned char serialNumber[4];
        // Bytes 521-550
        unsigned char modulePartnumber[partNumberSize];
        // Byte 551
        unsigned char moduleRevision;
        // Byte 552-553 DRAM Manufacturer ID Code
        unsigned char dramManufacturer[2];
        // Byte 554 DRAM stepping
        unsigned char dramStepping;

        // Block 9 - Manufacturing information

        // Bytes 555~639 (0x22B~27F): Manufacturer’s Specific Data
        unsigned char reserved_555_639[639 - 555 - 1];

        // End User bits (XMP/EXPO?)
        unsigned char endUser[1024 - 640 + 1];
    };
    #pragma pop(1)

    RawSPD rawSpd;

    // Raw SPD getters/setters
    const unsigned short getMinCycleTime();
    void setMinCycleTime(const unsigned short);
    const unsigned short getMaxCycleTime();
    void setMaxCycleTime(const unsigned short);

    const unsigned shortgettAA();
    void settAA(const unsigned short);
    const unsigned short gettRCD();
    void settRCD(const unsigned short);
    const unsigned short gettRP();
    void settRP(const unsigned short);
    const unsigned short gettRAS();
    void settRAS(const unsigned short);
    const unsigned short gettRC();
    void settRC(const unsigned short);
    const unsigned short gettWR();
    void settWR(const unsigned short);
    const unsigned short gettRFC1_slr();
    void settRFC1_slr(const unsigned short);
    const unsigned short gettRFC2_slr();
    void settRFC2_slr(const unsigned short);
    const unsigned short gettRFCsb_slr();
    void settRFCsb_slr(const unsigned short);
    const unsigned short gettRFC1_dlr();
    void settRFC1_dlr(const unsigned short);
    const unsigned short gettRFC2_dlr();
    void settRFC2_dlr(const unsigned short);
    const unsigned short gettRFCsb_dlr();
    void settRFCsb_dlr(const unsigned short);
    const unsigned short gettRRD_L();
    void settRRD_L(const unsigned short);
    const unsigned short gettRRD_L_lowerLimit();
    void settRRD_L_lowerLimit(const unsigned short);
    const unsigned short gettCCD_L();
    void settCCD_L(const unsigned short);
    const unsigned short gettCCD_L_lowerLimit();
    void settCCD_L_lowerLimit(const unsigned short);
    const unsigned short gettCCD_L_WR();
    void settCCD_L_WR(unsigned short);
    const unsigned short gettCCD_L_WR_lowerLimit();
    void settCCD_L_WR_lowerLimit(unsigned short);
    const unsigned short gettCCD_L_WR2();
    void settCCD_L_WR2(const unsigned short);
    const unsigned short gettCCD_L_WR2_lowerLimit();
    void settCCD_L_WR2_lowerLimit(const unsigned short);
    const unsigned short gettFAW();
    void settFAW(const unsigned short);
    const unsigned short gettFAW_lowerLimit();
    void settFAW_lowerLimit(const unsigned short);
    const unsigned short gettCCD_L_WTR();
    void settCCD_L_WTR(const unsigned short);
    const unsigned short gettCCD_L_WTR_lowerLimit();
    void settCCD_L_WTR_lowerLimit(const unsigned short);
    const unsigned short gettCCD_S_WTR();
    void settCCD_S_WTR(const unsigned short);
    const unsigned short gettCCD_S_WTR_lowerLimit();
    void settCCD_S_WTR_lowerLimit(const unsigned short);
    const unsigned short gettRTP();
    void settRTP(const unsigned short);
    const unsigned short gettRTP_lowerLimit();
    void settRTP_lowerLimit(const unsigned short);
    const unsigned short gettCCD_M();
    void settCCD_M(const unsigned short);
    const unsigned short gettCCD_M_lowerLimit();
    void settCCD_M_lowerLimit(const unsigned short);
    const unsigned short gettCCD_M_WR();
    void settCCD_M_WR(const unsigned short);
    const unsigned short gettCCD_M_WR_lowerLimit();
    void settCCD_M_WR_lowerLimit(const unsigned short);
    const unsigned short gettCCD_M_WTR();
    void settCCD_M_WTR(const unsigned short);
    const unsigned short gettCCD_M_WTR_lowerLimit();
    void settCCD_M_WTR_lowerLimit(const unsigned short);
    const unsigned short getBanksPerBankGroup();
    void setBanksPerBankGroup(const unsigned short);
    const unsigned short getBankGroups();
    void setBankGroups(const unsigned short);
    const unsigned short getColumnAddresses();
    void setColumnAddresses(const unsigned short);
    const unsigned short getRowAddresses();
    void setRowAddresses(const unsigned short);
    const unsigned short getDeviceWidth();
    void setDeviceWidth(const unsigned short);
    const unsigned short getManufacturingYear();
    void setManufacturingYear(const unsigned short);
    const unsigned short getManufacturingWeek();
    void setManufacturingWeek(const unsigned short);
    const std::string getPartNumber();
    void setPartNumber(const std::string);

    const unsigned short getCRC();
    void setCRC(const unsigned short);

    DDR5SPD(QByteArray);
};

#endif // DDR5SPD_H
