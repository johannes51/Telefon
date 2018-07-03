
//   "Aspen SIM800" is a comprehensive SIM800 library for simplified and in-depth chip access.
//   Copyright (C) 2016  Mattias Aabmets (https://github.com/aspenforest)
//
//   This API library is free software: you can redistribute it and/or modify
//   it under the terms of the GNU Affero General Public License as published
//   by the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   This API library is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
//   See the GNU Affero General Public License for more details.
//
//   You should have received a copy of the GNU Affero General Public License
//   along with this API library.  If not, see <http://www.gnu.org/licenses/>.

/*
█████████████████████████████████████████████████
████   ATcmd      Manpage       API Method   ████   Count: 55 commands
█████████████████████████████████████████████████
*/
public:
    /* AT+CACM    57 */    void callMeter          (CmdType, const char* = "");
    /* AT+CAMM    58 */    void callMeterMax       (CmdType, const char* = "");
    /* AT+CAOC    59 */    void chargeAdvice       (CmdType, const char* = "");
    /* AT+CBST    60 */    void dataCallService    (CmdType, const char* = "");
    /* AT+CCFC    61 */    void callForward        (CmdType, const char* = "");
    /* AT+CCWA    63 */    void callWait           (CmdType, const char* = "");
    /* AT+CEER    64 */    void errorReport        (CmdType, const char* = "");
    /* AT+CGMI    67 */    void reqMakerID         (CmdType);
    /* AT+CGMM    67 */    void reqDeviceModelID   (CmdType);
    /* AT+CGMR    68 */    void reqSoftwareID      (CmdType);
    /* AT+CGSN    68 */    void reqIMEI            (CmdType);
    /* AT+CSCS    69 */    void charset            (CmdType, const char* = "");
    /* AT+CSTA    70 */    void addressType        (CmdType, const char* = "");
    /* AT+CHLD    70 */    void callHold           (CmdType, const char* = "");
    /* AT+CIMI    71 */    void reqIMSI            (CmdType);
    /* AT+CLCC    72 */    void activeCalls        (CmdType, const char* = "");
    /* AT+CLCK    73 */    void facilityLock       (CmdType, const char* = "");
    /* AT+CLIP    75 */    void showCallerID       (CmdType, const char* = "");
    /* AT+CLIR    76 */    void hideSelfID         (CmdType, const char* = "");
    /* AT+CMEE    77 */    void deviceError        (CmdType, const char* = "");
    /* AT+COLP    78 */    void callerID           (CmdType, const char* = "");
    /* AT+COPS    80 */    void netOps             (CmdType, const char* = "");
    /* AT+CPAS    81 */    void activity           (CmdType);
    /* AT+CPBF    82 */    void pbFind             (CmdType, const char* = "");
    /* AT+CPBR    83 */    void pbRead             (CmdType, const char* = "");
    /* AT+CPBS    84 */    void pbStorage          (CmdType, const char* = "");
    /* AT+CPBW    85 */    void pbWrite            (CmdType, const char* = "");
    /* AT+CPIN    86 */    void pinCode            (CmdType, const char* = "");
    /* AT+CPWD    87 */    void changePwd          (CmdType, const char* = "");
    /* AT+CR      88 */    void serviceReport      (CmdType, const char* = "");
    /* AT+CRC     89 */    void ringCodeMode       (CmdType, const char* = "");
    /* AT+CREG    90 */    void netReg             (CmdType, const char* = "");
    /* AT+CRLP    92 */    void radioLinkParams    (CmdType, const char* = "");
    /* AT+CRSM    92 */    void simRawAccess       (CmdType, const char* = "");
    /* AT+CSQ     93 */    void signalQuality      (CmdType);
    /* AT+VTD     94 */    void dtmfDuration       (CmdType, const char* = "");
    /* AT+VTS     95 */    void dtmfPlay           (CmdType, const char* = "");
    /* AT+CMUX    96 */    void muxControl         (CmdType, const char* = "");
    /* AT+CNUM    97 */    void getSelfAddr        (CmdType);
    /* AT+CPOL    98 */    void prefOperators      (CmdType, const char* = "");
    /* AT+COPN    99 */    void listAllOperators   (CmdType);
    /* AT+CFUN   100 */    void deviceMode         (CmdType, const char* = "");
    /* AT+CCLK   101 */    void clock              (CmdType, const char* = "");
    /* AT+CSIM   101 */    void simStrAccess       (CmdType, const char* = "");
    /* AT+CALM   102 */    void alertMode          (CmdType, const char* = "");
    /* AT+CALS   103 */    void alertSound         (CmdType, const char* = "");
    /* AT+CRSL   104 */    void ringerVolume       (CmdType, const char* = "");
    /* AT+CLVL   104 */    void loudSpeakerVol     (CmdType, const char* = "");
    /* AT+CMUT   105 */    void mute               (CmdType, const char* = "");
    /* AT+CPUC   106 */    void pricePerUnit       (CmdType, const char* = "");
    /* AT+CCWE   107 */    void callMeterMaxEvent  (CmdType, const char* = "");
    /* AT+CBC    108 */    void battery            (CmdType);
    /* AT+CUSD   108 */    void usd                (CmdType, const char* = "");
    /* AT+CSSN   109 */    void ssn                (CmdType, const char* = "");
    /* AT+DDET   333 */    void dtmfDetect         (CmdType, const char* = ""); 