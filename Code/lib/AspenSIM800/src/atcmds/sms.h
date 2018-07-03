
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
██████████████████████████████████████████████████
████   ATcmd      Manpage        API Method   ████   Count: 16 commands
██████████████████████████████████████████████████
*/
public:
    /* AT+CMGD    112 */    void smsDel            (CmdType, const char* = "");
    /* AT+CMGF    113 */    void smsFormat         (CmdType, const char* = "");
    /* AT+CMGL    114 */    void smsList           (CmdType, const char* = "");
    /* AT+CMGR    117 */    void smsRead           (CmdType, const char* = "");
    /* AT+CMGS    120 */    void smsSend           (char*, char*);
    /* AT+CMGW    121 */    void smsWriteToStore   (char*, char*);
    /* AT+CMSS    123 */    void smsSendFromStore  (CmdType, const char* = "");
    /* AT+CNMI    124 */    void smsNotifyNew      (CmdType, const char* = "");
    /* AT+CPMS    126 */    void smsStorage        (CmdType, const char* = "");
    /* AT+CRES    127 */    void smsRestoreCfg     (CmdType, const char* = "");
    /* AT+CSAS    128 */    void smsSaveCfg        (CmdType, const char* = "");
    /* AT+CSCA    129 */    void smsCenterAddress  (CmdType, const char* = "");
    /* AT+CSCB    130 */    void smsCellCast       (CmdType, const char* = "");
    /* AT+CSDH    131 */    void smsGetParams      (CmdType, const char* = "");
    /* AT+CSMP    132 */    void smsSetParams      (CmdType, const char* = "");
    /* AT+CSMS    133 */    void smsService        (CmdType, const char* = "");

private:
    void smsHelper(const char*);