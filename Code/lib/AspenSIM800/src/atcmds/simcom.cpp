
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


#include <SIM800.h>


// ============================================================
void SIM800::sideToneGain(CmdType type, const char* str) {
    outBuilder(type, str, P("SIDET"));
    print(ioBuffer);
}

// ============================================================
void SIM800::powerOff(const char* str) {
    outBuilder(SET, str, P("CPOWD"));
    print(ioBuffer);
}

// ============================================================
void SIM800::pinCodeTriesLeft() {
    outBuilder(EXE, "", P("SPIC"));
    print(ioBuffer);
}

// ============================================================
void SIM800::micGain(CmdType type, const char* str) {
    outBuilder(type, str, P("CMIC"));
    print(ioBuffer);
}

// ============================================================
void SIM800::alarmTime(CmdType type, const char* str) {
    outBuilder(type, str, P("CALA"));
    print(ioBuffer);
}

// ============================================================
void SIM800::delAlarm(CmdType type, const char* str) {
    outBuilder(type, str, P("CALD"));
    print(ioBuffer);
}

// ============================================================
void SIM800::readAdc(CmdType type) {
    outBuilder(type, "", P("CADC"));
    print(ioBuffer);
}

// ============================================================
void SIM800::singleNumScheme(CmdType type, const char* str) {
    outBuilder(type, str, P("CSNS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::resetCellCast() {
    outBuilder(EXE, "", P("CDSCB"));
    print(ioBuffer);
}

// ============================================================
void SIM800::cfgAltModeCalls(CmdType type, const char* str) {
    outBuilder(type, str, P("CMOD"));
    print(ioBuffer);
}

// ============================================================
void SIM800::riPinUrc(CmdType type, const char* str) {
    outBuilder(type, str, P("CFGRI"));
    print(ioBuffer);
}

// ============================================================
void SIM800::timeStamp(CmdType type, const char* str) {
    outBuilder(type, str, P("CLTS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::dtmfLocalTone(CmdType type, const char* str) {
    outBuilder(type, str, P("CLDTMF"));
    print(ioBuffer);
}

// ============================================================
void SIM800::indicateCallEnd(CmdType type, const char* str) {
    outBuilder(type, str, P("CDRIND"));
    print(ioBuffer);
}

// ============================================================
void SIM800::serviceProvider() {
    outBuilder(GET, "", P("CSPN"));
    print(ioBuffer);
}

// ============================================================
void SIM800::voiceMail(CmdType type, const char* str) {
    outBuilder(type, str, P("CCVM"));
    print(ioBuffer);
}

// ============================================================
void SIM800::opBand(CmdType type, const char* str) {
    outBuilder(type, str, P("CBAND"));
    print(ioBuffer);
}

// ============================================================
void SIM800::handsFree(CmdType type, const char* str) {
    outBuilder(type, str, P("CHF"));
    print(ioBuffer);
}

// ============================================================
void SIM800::swapAudio(CmdType type, const char* str) {
    outBuilder(type, str, P("CHFA"));
    print(ioBuffer);
}

// ============================================================
void SIM800::slowClock(CmdType type, const char* str) {
    outBuilder(type, str, P("CSCLK"));
    print(ioBuffer);
}

// ============================================================
void SIM800::engMode(CmdType type, const char* str) {
    outBuilder(type, str, P("CENG"));
    print(ioBuffer);
}

// ============================================================
void SIM800::smsZeroToSIM(CmdType type, const char* str) {
    outBuilder(type, str, P("SCLASS0"));
    print(ioBuffer);
}

// ============================================================
void SIM800::simCardID(CmdType type) {
    outBuilder(type, "", P("CCID"));
    print(ioBuffer);
}

// ============================================================
void SIM800::temperature(CmdType type, const char* str) {
    outBuilder(type, str, P("CMTE"));
    print(ioBuffer);
}

// ============================================================
void SIM800::delAllMsg(CmdType type, const char* str) {
    outBuilder(type, str, P("CMGDA"));
    print(ioBuffer);
}

// ============================================================
void SIM800::stkPlayTone(CmdType type, const char* str) {
    outBuilder(type, str, P("STTONE"));
    print(ioBuffer);
}

// ============================================================
void SIM800::toneGen(CmdType type, const char* str) {
    outBuilder(type, str, P("SIMTONE"));
    print(ioBuffer);
}

// ============================================================
void SIM800::alphaString(CmdType type, const char* str) {
    outBuilder(type, str, P("CCPD"));
    print(ioBuffer);
}

// ============================================================
void SIM800::simGroupID() {
    outBuilder(EXE, "", P("CGID"));
    print(ioBuffer);
}

// ============================================================
void SIM800::originCallState(CmdType type, const char* str) {
    outBuilder(type, str, P("MORING"));
    print(ioBuffer);
}

// ============================================================
void SIM800::smsHexMode(CmdType type, const char* str) {
    outBuilder(type, str, P("CMGHEX"));
    print(ioBuffer);
}

// ============================================================
void SIM800::smsDeviceCompat(CmdType type, const char* str) {
    outBuilder(type, str, P("CCODE"));
    print(ioBuffer);
}

// ============================================================
void SIM800::cfgInitUrc(CmdType type, const char* str) {
    outBuilder(type, str, P("CIURC"));
    print(ioBuffer);
}

// ============================================================
void SIM800::setSuperPwd(const char* str) {
    outBuilder(SET, str, P("CPSPWD"));
    print(ioBuffer);
}

// ============================================================
void SIM800::signalQualityURC(CmdType type, const char* str) {
    outBuilder(type, str, P("EXUNSOL"));
    print(ioBuffer);
}

// ============================================================
void SIM800::gprsMultiClass(CmdType type, const char* str) {
    outBuilder(type, str, P("CGMSCLASS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::getFlashMem() {
    outBuilder(GET, "", P("CDEVICE"));
    print(ioBuffer);
}

// ============================================================
void SIM800::queryCallReady(CmdType type) {
    outBuilder(type, "", P("CCALR"));
    print(ioBuffer);
}

// ============================================================
void SIM800::getPII() {
    outBuilder(EXE, "", P("GSV"));
    print(ioBuffer);
}

// ============================================================
void SIM800::gpioCtrl(CmdType type, const char* str) {
    outBuilder(type, str, P("SGPIO"));
    print(ioBuffer);
}


// ============================================================
void SIM800::pwmGen(CmdType type, const char* str) {
    outBuilder(type, str, P("SPWM"));
    print(ioBuffer);
}

// ============================================================
void SIM800::echoCtrl(CmdType type, const char* str) {
    outBuilder(type, str, P("ECHO"));
    print(ioBuffer);
}

// ============================================================
void SIM800::autoAudioSwitch(CmdType type, const char* str) {
    outBuilder(type, str, P("CAAS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::voiceEncoderCtrl(CmdType type, const char* str) {
    outBuilder(type, str, P("SVR"));
    print(ioBuffer);
}

// ============================================================
void SIM800::gsmBusy(CmdType type, const char* str) {
    outBuilder(type, str, P("GSMBUSY"));
    print(ioBuffer);
}

// ============================================================
void SIM800::emergencyNumList(CmdType type, const char* str) {
    outBuilder(type, str, P("CEMNL"));
    print(ioBuffer);
}

// ============================================================
void SIM800::arfcnLock(CmdType type, const char* str) {
    outBuilder(type, str, P("AT*CELLLOCK"), false);
    print(ioBuffer);
}

// ============================================================
void SIM800::netLightPeriod(CmdType type, const char* str) {
    outBuilder(type, str, P("SLEDS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::buzzerRingtone(CmdType type, const char* str) {
    outBuilder(type, str, P("CBUZZERRING"));
    print(ioBuffer);
}

// ============================================================
void SIM800::micCtrl(CmdType type, const char* str) {
    outBuilder(type, str, P("CEXTERNTONE"));
    print(ioBuffer);
}

// ============================================================
void SIM800::netLight(CmdType type, const char* str) {
    outBuilder(type, str, P("CNETLIGHT"));
    print(ioBuffer);
}

// ============================================================
void SIM800::whiteList(CmdType type, const char* str) {
    outBuilder(type, str, P("CWHITELIST"));
    print(ioBuffer);
}

// ============================================================
void SIM800::detectSimCard(CmdType type, const char* str) {
    outBuilder(type, str, P("CSDT"));
    print(ioBuffer);
}

// ============================================================
void SIM800::simPresent(CmdType type, const char* str) {
    outBuilder(type, str, P("CSMINS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::gprsNetLight(CmdType type, const char* str) {
    outBuilder(type, str, P("CSGS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::micBias(CmdType type, const char* str) {
    outBuilder(type, str, P("CMICBIAS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::playAudioIntoCall(CmdType type, const char* str) {
    outBuilder(type, str, P("DTAM"));
    print(ioBuffer);
}

// ============================================================
void SIM800::detectJamming(CmdType type, const char* str) {
    outBuilder(type, str, P("SJDR"));
    print(ioBuffer);
}

// ============================================================
void SIM800::pcmCfg(CmdType type, const char* str) {
    outBuilder(type, str, P("CPCMCFG"));
    print(ioBuffer);
}

// ============================================================
void SIM800::pcmSyncParam(CmdType type, const char* str) {
    outBuilder(type, str, P("CPCMSYNC"));
    print(ioBuffer);
}

// ============================================================
void SIM800::detectAntenna(CmdType type, const char* str) {
    outBuilder(type, str, P("CANT"));
    print(ioBuffer);
}

// ============================================================
void SIM800::agcCfg(CmdType type, const char* str) {
    outBuilder(type, str, P("CAGCSET"));
    print(ioBuffer);
}

// ============================================================
void SIM800::pcmSwitchSD(CmdType type, const char* str) {
    outBuilder(type, str, P("SD2PCM"));
    print(ioBuffer);
}

// ============================================================
void SIM800::detectKeypad(CmdType type, const char* str) {
    outBuilder(type, str, P("SKPD"));
    print(ioBuffer);
}

// ============================================================
void SIM800::toneStringGen(CmdType type, const char* str) {
    outBuilder(type, str, P("SIMTONEX"));
    print(ioBuffer);
}

// ============================================================
void SIM800::roamingState() {
    outBuilder(EXE, "", P("CROAMING"));
    print(ioBuffer);
}

// ============================================================
void SIM800::netScan(CmdType type, const char* str) {
    outBuilder(type, str, P("CNETSCAN"));
    print(ioBuffer);
}

// ============================================================
void SIM800::dualSerialPort(CmdType type, const char* str) {
    outBuilder(type, str, P("CMNRP"));
    print(ioBuffer);
}

// ============================================================
void SIM800::edgeCfg(CmdType type, const char* str) {
    outBuilder(type, str, P("CEGPRS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::gpioIndex(CmdType type, const char* str) {
    outBuilder(type, str, P("CGPIO"));
    print(ioBuffer);
}

// ============================================================
void SIM800::playAudio(CmdType type, const char* str) {
    outBuilder(type, str, P("CMEDPLAY"));
    print(ioBuffer);
}

// ============================================================
void SIM800::audioVolume(CmdType type, const char* str) {
    outBuilder(type, str, P("CMEDIAVOL"));
    print(ioBuffer);
}

// ============================================================
void SIM800::atcmdSoundLevel(CmdType type, const char* str) {
    outBuilder(type, str, P("SNDLEVEL"));
    print(ioBuffer);
}

// ============================================================
void SIM800::chargeCtrl(CmdType type, const char* str) {
    outBuilder(type, str, P("ECHARGE"));
    print(ioBuffer);
}

// ============================================================
void SIM800::simPollInterval(CmdType type, const char* str) {
    outBuilder(type, str, P("SIMTIMER"));
    print(ioBuffer);
}

// ============================================================
void SIM800::enhanceSpeech(CmdType type, const char* str) {
    outBuilder(type, str, P("SPE"));
    print(ioBuffer);
}

// ============================================================
void SIM800::getConcatMsgIndex(CmdType type) {
    outBuilder(type, "", P("CCONCINDEX"));
    print(ioBuffer);
}

// ============================================================
void SIM800::sdModeSwitch(CmdType type, const char* str) {
    outBuilder(type, str, P("SDMODE"));
    print(ioBuffer);
}

// ============================================================
void SIM800::smsResendCtrl(CmdType type, const char* str) {
    outBuilder(type, str, P("SRSPT"));
    print(ioBuffer);
}

// ============================================================
void SIM800::record(CmdType type, const char* str) {
    outBuilder(type, str, P("CREC"));
    print(ioBuffer);
}

// ============================================================
void SIM800::recordToUart(CmdType type, const char* str) {
    outBuilder(type, str, P("CRECORD"));
    print(ioBuffer);
}

// ============================================================
void SIM800::textToSpeech(CmdType type, const char* str) {
    outBuilder(type, str, P("CTTS"));
    print(ioBuffer);
}

// ============================================================
void SIM800::textToSpeechCfg(CmdType type, const char* str) {
    outBuilder(type, str, P("CTTSPARAM"));
    print(ioBuffer);
}

// ============================================================
void SIM800::textToSpeechRing(CmdType type, const char* str) {
    outBuilder(type, str, P("CTTSRING"));
    print(ioBuffer);
}