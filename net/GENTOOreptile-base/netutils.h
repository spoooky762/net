typedef struct ipsites {
	char *site;
	char *match;
	BOOL tried;
} IPSITES;

char *GetIP(SOCKET sock);
DWORD WINAPI GetExIP(LPVOID param);
BOOL PrivateIP(const char *ip);
USHORT checksum(USHORT *buffer, int size);
unsigned long ResolveAddress(char *szHost);
