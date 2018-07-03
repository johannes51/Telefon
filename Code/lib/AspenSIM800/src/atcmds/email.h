
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
█████████████████████████████████████████████████████
████   ATcmd         Manpage        API Method   ████   Count: 22 commands
█████████████████████████████████████████████████████
*/
public:
    /* AT+EMAILCID   291 */    void mailBearerID  (CmdType, const char* = "");
    /* AT+EMAILTO    291 */    void mailTimeout   (CmdType, const char* = "");
    /* AT+SMTPSRV    292 */    void smtpServer    (CmdType, const char* = "");
    /* AT+SMTPAUTH   293 */    void smtpAuth      (CmdType, const char* = "");
    /* AT+SMTPFROM   294 */    void smtpFrom      (CmdType, const char* = "");
    /* AT+SMTPRCPT   295 */    void smtpTo        (CmdType, const char* = "");
    /* AT+SMTPSUB    296 */    void smtpSubject   (CmdType, const char* = "");
    /* AT+SMTPBODY   296 */    void smtpBody      (CmdType, const char* = "");
    /* AT+SMTPFILE   297 */    void smtpFile      (CmdType, const char* = "");
    /* AT+SMTPSEND   298 */    void smtpSend      (CmdType);
    /* AT+SMTPFT     299 */    void smtpFilesend  (CmdType, const char* = "");
    /* AT+SMTPCS     300 */    void smtpCharset   (CmdType, const char* = "");
    /* AT+POP3SRV    301 */    void popCfg        (CmdType, const char* = "");
    /* AT+POP3IN     302 */    void popLogin      (CmdType);
    /* AT+POP3NUM    302 */    void popInbox      (CmdType);
    /* AT+POP3LIST   303 */    void popMailSize   (CmdType, const char* = "");
    /* AT+POP3UIDL   304 */    void popMailUID    (CmdType, const char* = "");
    /* AT+POP3CMD    305 */    void popMultiGet   (CmdType, const char* = "");
    /* AT+POP3READ   307 */    void popMultiRead  (CmdType, const char* = "");
    /* AT+POP3DEL    308 */    void popMarkDel    (CmdType, const char* = "");
    /* AT+POP3RSET   309 */    void popUnmarkDel  (CmdType);
    /* AT+POP3OUT    310 */    void popLogout     (CmdType);