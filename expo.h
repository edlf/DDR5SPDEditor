#ifndef EXPO_H
#define EXPO_H

#include "ddr5spd_structs.h"
#include <string>

using namespace ddr5_structs;

class EXPO_Profile {
public:
  EXPO_Profile(ddr5_structs::EXPO_ProfileStruct &);
  EXPO_Profile();

  // Voltages
  const unsigned short getVPP();
  void setVPP(const unsigned short);

  const unsigned short getVDD();
  void setVDD(const unsigned short);

  const unsigned short getVDDQ();
  void setVDDQ(const unsigned short);

  // Cycle + CAS
  const unsigned short getMinCycleTime();
  void setMinCycleTime(const unsigned short);
  const unsigned int getFrequency();
  const unsigned int getMT();

  // Timings
  const unsigned short gettAA();
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

  const unsigned short gettRFC1();
  void settRFC1(const unsigned short);

  const unsigned short gettRFC2();
  void settRFC2(const unsigned short);

  const unsigned short gettRFC();
  void settRFC(const unsigned short);

  const unsigned short gettRRD_L();
  void settRRD_L(const unsigned short);

  const unsigned short gettCCD_L_WR();
  void settCCD_L_WR(const unsigned short);

  const unsigned short gettCCD_L_WR2();
  void settCCD_L_WR2(const unsigned short);

  const unsigned short gettCCD_L_WTR();
  void settCCD_L_WTR(const unsigned short);

  const unsigned short gettCCD_S_WTR();
  void settCCD_S_WTR(const unsigned short);

  const unsigned short gettCCD_L();
  void settCCD_L(const unsigned short);

  const unsigned short gettRTP();
  void settRTP(const unsigned short);

  const unsigned short gettFAW();
  void settFAW(const unsigned short);

  const unsigned short gettAA_tick();
  void settAA_tick(const unsigned short);

  const unsigned short gettRCD_tick();
  void settRCD_tick(const unsigned short);

  const unsigned short gettRP_tick();
  void settRP_tick(const unsigned short);

  const unsigned short gettRAS_tick();
  void settRAS_tick(const unsigned short);

  const unsigned short gettRC_tick();
  void settRC_tick(const unsigned short);

  const unsigned short gettWR_tick();
  void settWR_tick(const unsigned short);

  const unsigned short gettRFC1_tick();
  void settRFC1_tick(const unsigned short);

  const unsigned short gettRFC2_tick();
  void settRFC2_tick(const unsigned short);

  const unsigned short gettRFC_tick();
  void settRFC_tick(const unsigned short);

  const unsigned short gettRRD_L_tick();
  void settRRD_L_tick(const unsigned short);

  const unsigned short gettCCD_L_WR_tick();
  void settCCD_L_WR_tick(const unsigned short);

  const unsigned short gettCCD_L_WR2_tick();
  void settCCD_L_WR2_tick(const unsigned short);

  const unsigned short gettCCD_L_WTR_tick();
  void settCCD_L_WTR_tick(const unsigned short);

  const unsigned short gettCCD_S_WTR_tick();
  void settCCD_S_WTR_tick(const unsigned short);

  const unsigned short gettCCD_L_tick();
  void settCCD_L_tick(const unsigned short);

  const unsigned short gettRTP_tick();
  void settRTP_tick(const unsigned short);

  const unsigned short gettFAW_tick();
  void settFAW_tick(const unsigned short);

  const unsigned short getDimmsChannel();
  void setDimmsChannel(const unsigned short);

  const unsigned short getCRC();
  void setCRC(const unsigned short);

  void wipeProfile();
  void resetProfile();
  void copyFromXMP(const XMP_ProfileStruct &xmpProfile);

  const bool hasData();

  EXPO_ProfileStruct getCopy();
  void import(const EXPO_ProfileStruct);

private:
  EXPO_ProfileStruct &expoProfileStruct;
};

class EXPO_Bundle {
public:
  EXPO_Bundle(EXPO_Struct &);

  void enableMagic();
  void clearMagic();
  bool isMagicPresent();

  const bool isEXPO1Enabled();
  void setEXPO1Enabled(const bool);

  const bool isEXPO2Enabled();
  void setEXPO2Enabled(const bool);

  const unsigned short getCRC();
  void setCRC(const unsigned short);

  void fixCRC();

  void resetAndCreateSample();
  void wipe();

  EXPO_Profile profile1;
  EXPO_Profile profile2;

private:
  EXPO_Struct &expoStruct;
};

#endif // EXPO_H
