
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
████████████████████████████████████████████████████████
████   ATcmd            Manpage        API Method   ████   Total: 84 commands
████████████████████████████████████████████████████████
*/
public:
    /* AT+SIDET         145 */    void sideToneGain        (CmdType, const char* = "");
    /* AT+CPOWD         146 */    void powerOff            (const char*);
    /* AT+SPIC          146 */    void pinCodeTriesLeft    ();
    /* AT+CMIC          146 */    void micGain             (CmdType, const char* = "");
    /* AT+CALA          148 */    void alarmTime           (CmdType, const char* = "");
    /* AT+CALD          149 */    void delAlarm            (CmdType, const char* = "");
    /* AT+CADC          149 */    void readAdc             (CmdType);
    /* AT+CSNS          150 */    void singleNumScheme     (CmdType, const char* = "");
    /* AT+CDSCB         151 */    void resetCellCast       ();
    /* AT+CMOD          151 */    void cfgAltModeCalls     (CmdType, const char* = "");
    /* AT+CFGRI         151 */    void riPinUrc            (CmdType, const char* = "");
    /* AT+CLTS          152 */    void timeStamp           (CmdType, const char* = "");
    /* AT+CLDTMF        154 */    void dtmfLocalTone       (CmdType, const char* = "");
    /* AT+CDRIND        155 */    void indicateCallEnd     (CmdType, const char* = "");
    /* AT+CSPN          156 */    void serviceProvider     ();
    /* AT+CCVM          156 */    void voiceMail           (CmdType, const char* = "");
    /* AT+CBAND         157 */    void opBand              (CmdType, const char* = "");
    /* AT+CHF           158 */    void handsFree           (CmdType, const char* = "");
    /* AT+CHFA          159 */    void swapAudio           (CmdType, const char* = "");
    /* AT+CSCLK         160 */    void slowClock           (CmdType, const char* = "");
    /* AT+CENG          161 */    void engMode             (CmdType, const char* = "");
    /* AT+SCLASS0       163 */    void smsZeroToSIM        (CmdType, const char* = "");
    /* AT+CCID          164 */    void simCardID           (CmdType);
    /* AT+CMTE          164 */    void temperature         (CmdType, const char* = "");
    /* AT+CMGDA         165 */    void delAllMsg           (CmdType, const char* = "");
    /* AT+STTONE        166 */    void stkPlayTone         (CmdType, const char* = "");
    /* AT+SIMTONE       167 */    void toneGen             (CmdType, const char* = "");
    /* AT+CCPD          168 */    void alphaString         (CmdType, const char* = "");
    /* AT+CGID          168 */    void simGroupID          ();
    /* AT+MORING        169 */    void originCallState     (CmdType, const char* = "");
    /* AT+CMGHEX        170 */    void smsHexMode          (CmdType, const char* = "");
    /* AT+CCODE         170 */    void smsDeviceCompat     (CmdType, const char* = "");
    /* AT+CIURC         171 */    void cfgInitUrc          (CmdType, const char* = "");
    /* AT+CPSPWD        172 */    void setSuperPwd         (const char*);
    /* AT+EXUNSOL       172 */    void signalQualityURC    (CmdType, const char* = "");
    /* AT+CGMSCLASS     173 */    void gprsMultiClass      (CmdType, const char* = "");
    /* AT+CDEVICE       174 */    void getFlashMem         ();
    /* AT+CCALR         174 */    void queryCallReady      (CmdType);
    /* AT+GSV           174 */    void getPII              ();
    /* AT+SGPIO         175 */    void gpioCtrl            (CmdType, const char* = "");
    /* AT+SPWM          176 */    void pwmGen              (CmdType, const char* = "");
    /* AT+ECHO          176 */    void echoCtrl            (CmdType, const char* = "");
    /* AT+CAAS          177 */    void autoAudioSwitch     (CmdType, const char* = "");
    /* AT+SVR           178 */    void voiceEncoderCtrl    (CmdType, const char* = "");
    /* AT+GSMBUSY       179 */    void gsmBusy             (CmdType, const char* = "");
    /* AT+CEMNL         180 */    void emergencyNumList    (CmdType, const char* = "");
    /* AT*CELLLOCK      181 */    void arfcnLock           (CmdType, const char* = "");
    /* AT+SLEDS         182 */    void netLightPeriod      (CmdType, const char* = "");
    /* AT+CBUZZERRING   183 */    void buzzerRingtone      (CmdType, const char* = "");
    /* AT+CEXTERNTONE   183 */    void micCtrl             (CmdType, const char* = "");
    /* AT+CNETLIGHT     184 */    void netLight            (CmdType, const char* = "");
    /* AT+CWHITELIST    185 */    void whiteList           (CmdType, const char* = "");
    /* AT+CSDT          186 */    void detectSimCard       (CmdType, const char* = "");
    /* AT+CSMINS        186 */    void simPresent          (CmdType, const char* = "");
    /* AT+CSGS          187 */    void gprsNetLight        (CmdType, const char* = "");
    /* AT+CMICBIAS      188 */    void micBias             (CmdType, const char* = "");
    /* AT+DTAM          189 */    void playAudioIntoCall   (CmdType, const char* = "");
    /* AT+SJDR          189 */    void detectJamming       (CmdType, const char* = "");
    /* AT+CPCMCFG       191 */    void pcmCfg              (CmdType, const char* = "");
    /* AT+CPCMSYNC      192 */    void pcmSyncParam        (CmdType, const char* = "");
    /* AT+CANT          193 */    void detectAntenna       (CmdType, const char* = "");
    /* AT+CAGCSET       194 */    void agcCfg              (CmdType, const char* = "");
    /* AT+SD2PCM        194 */    void pcmSwitchSD         (CmdType, const char* = "");
    /* AT+SKPD          194 */    void detectKeypad        (CmdType, const char* = "");
    /* AT+SIMTONEX      196 */    void toneStringGen       (CmdType, const char* = "");
    /* AT+CROAMING      197 */    void roamingState        ();
    /* AT+CNETSCAN      197 */    void netScan             (CmdType, const char* = "");
    /* AT+CMNRP         198 */    void dualSerialPort      (CmdType, const char* = "");
    /* AT+CEGPRS        199 */    void edgeCfg             (CmdType, const char* = "");
    /* AT+CGPIO         200 */    void gpioIndex           (CmdType, const char* = "");
    /* AT+CMEDPLAY      201 */    void playAudio           (CmdType, const char* = "");
    /* AT+CMEDIAVOL     202 */    void audioVolume         (CmdType, const char* = "");
    /* AT+SNDLEVEL      202 */    void atcmdSoundLevel     (CmdType, const char* = "");
    /* AT+ECHARGE       203 */    void chargeCtrl          (CmdType, const char* = "");
    /* AT+SIMTIMER      204 */    void simPollInterval     (CmdType, const char* = "");
    /* AT+SPE           204 */    void enhanceSpeech       (CmdType, const char* = "");
    /* AT+CCONCINDEX    205 */    void getConcatMsgIndex   (CmdType);
    /* AT+SDMODE        205 */    void sdModeSwitch        (CmdType, const char* = "");
    /* AT+SRSPT         206 */    void smsResendCtrl       (CmdType, const char* = "");
    /* AT+CREC          335 */    void record              (CmdType, const char* = "");
    /* AT+CRECORD       338 */    void recordToUart        (CmdType, const char* = "");
    /* AT+CTTS          340 */    void textToSpeech        (CmdType, const char* = "");
    /* AT+CTTSPARAM     341 */    void textToSpeechCfg     (CmdType, const char* = "");
    /* AT+CTTSRING      342 */    void textToSpeechRing    (CmdType, const char* = "");