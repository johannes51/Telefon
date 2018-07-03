
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
███████████████████████████████████████████████████████
████   ATcmd           Manpage        API Method   ████   Count: 36 commands
███████████████████████████████████████████████████████
*/
public:
    /* AT+CIPMUX       221 */    void ipMultiConn      (CmdType, const char* = "");
    /* AT+CIPSTART     221 */    void ipOpen           (CmdType, const char* = "");
    /* AT+CIPSEND      223 */    void ipSend           (CmdType, const char* = "");
    /* AT+CIPQSEND     225 */    void ipQuicksend      (CmdType, const char* = "");
    /* AT+CIPACK       226 */    void ipAck            (CmdType, const char* = "");
    /* AT+CIPCLOSE     227 */    void ipClose          (CmdType, const char* = "");
    /* AT+CIPSHUT      227 */    void ipDeactivate     (CmdType);
    /* AT+CLPORT       228 */    void ipPort           (CmdType, const char* = "");
    /* AT+CSTT         229 */    void ipAccess         (CmdType, const char* = "");
    /* AT+CIICR        230 */    void ipBegin          (CmdType);
    /* AT+CIFSR        230 */    void ipGetLocalAddr   (CmdType);
    /* AT+CIPSTATUS    231 */    void ipStatus         (CmdType, const char* = "");
    /* AT+CDNSCFG      232 */    void ipDnsCfg         (CmdType, const char* = "");
    /* AT+CDNSGIP      233 */    void ipGetNameAddr    (CmdType, const char* = "");
    /* AT+CIPHEAD      234 */    void ipAddHead        (CmdType, const char* = "");
    /* AT+CIPATS       234 */    void ipAutoSendTimer  (CmdType, const char* = "");
    /* AT+CIPSPRT      235 */    void ipSendPrompt     (CmdType, const char* = "");
    /* AT+CIPSERVER    236 */    void ipServer         (CmdType, const char* = "");
    /* AT+CIPCSGP      237 */    void ipConnMode       (CmdType, const char* = "");
    /* AT+CIPSRIP      238 */    void ipShowRemoteID   (CmdType, const char* = "");
    /* AT+CIPDPDP      239 */    void ipNetTiming      (CmdType, const char* = "");
    /* AT+CIPMODE      239 */    void ipAppMode        (CmdType, const char* = "");
    /* AT+CIPCCFG      240 */    void ipTransferCfg    (CmdType, const char* = "");
    /* AT+CIPSHOWTP    241 */    void ipShowProtocol   (CmdType, const char* = "");
    /* AT+CIPUDPMODE   242 */    void ipUdpMode        (CmdType, const char* = "");
    /* AT+CIPRXGET     243 */    void ipManualData     (CmdType, const char* = "");
    /* AT+CIPSCONT     245 */    void ipSaveCfg        (CmdType);
    /* AT+CIPRDTIMER   246 */    void ipRemoteTimer    (CmdType, const char* = "");
    /* AT+CIPSGTXT     247 */    void ipMultiPdpCfg    (CmdType, const char* = "");
    /* AT+CIPTKA       248 */    void ipKeepAlive      (CmdType, const char* = "");
    /* AT+SAPBR        249 */    void ipBearer         (CmdType, const char* = "");
    /* AT+CIPPING      251 */    void ipPing           (CmdType, const char* = "");
    /* AT+CIPCTL       252 */    void ipEchoReply      (CmdType, const char* = "");
    /* AT+CIPFLT       253 */    void ipFilter         (CmdType, const char* = "");
    /* AT+CIPBEIPING   254 */    void ipAnswerPings    (CmdType, const char* = "");
    /* AT+CIPGSMLOC    288 */    void ipGsmLoc         (CmdType, const char* = "");

private:
    void ipHelper(const char *);
