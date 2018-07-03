
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
████   ATcmd           Manpage        API Method   ████   Count: 25 commands
███████████████████████████████████████████████████████
*/
public:
    /* AT+CMMSCURL      312 */    void mmsCenterUrl    (CmdType, const char* = "");
    /* AT+CMMSPROTO     312 */    void mmsProxy        (CmdType, const char* = "");
    /* AT+CMMSCID       313 */    void mmsNetwork      (CmdType, const char* = "");
    /* AT+CMMSSENDCFG   314 */    void mmsCfgSend      (CmdType, const char* = "");
    /* AT+CMMSEDIT      315 */    void mmsEdit         (CmdType, const char* = "");
    /* AT+CMMSDOWN      316 */    void mmsDownFile     (CmdType, const char* = "");
    /* AT+CMMSDELFILE   317 */    void mmsDelFile      (CmdType, const char* = "");
    /* AT+CMMSSEND      318 */    void mmsSend         (CmdType, const char* = "");
    /* AT+CMMSRECP      319 */    void mmsAddRecp      (CmdType, const char* = "");
    /* AT+CMMSCC        319 */    void mmsAddCopyRecp  (CmdType, const char* = "");
    /* AT+CMMSBCC       320 */    void mmsAddBccRecp   (CmdType, const char* = "");
    /* AT+CMMSDELRECP   321 */    void mmsDelRecp      (CmdType, const char* = "");
    /* AT+CMMSDELCC     321 */    void mmsDelCopyRecp  (CmdType, const char* = "");
    /* AT+CMMSDELBCC    322 */    void mmsDelBccRecp   (CmdType, const char* = "");
    /* AT+CMMSRECV      323 */    void mmsGet          (CmdType, const char* = "");
    /* AT+CMMSVIEW      324 */    void mmsDetails      (CmdType);
    /* AT+CMMSREAD      325 */    void mmsRead         (CmdType, const char* = "");
    /* AT+CMMSRDPUSH    325 */    void mmsReadPush     (CmdType, const char* = "");
    /* AT+CMMSUA        327 */    void mmsUserAgent    (CmdType, const char* = "");
    /* AT+CMMSPROFILE   328 */    void mmsUserProfile  (CmdType, const char* = "");
    /* AT+CMMSTIMEOUT   328 */    void mmsTimeout      (CmdType, const char* = "");
    /* AT+CMMSSTATUS    329 */    void mmsStatus       (CmdType);
    /* AT+CMMSINIT      330 */    void mmsBegin        (CmdType);
    /* AT+CMMSTERM      330 */    void mmsEnd          (CmdType);
    /* AT+CMMSSCONT     331 */    void mmsSaveCfg      (CmdType);