/*
NSABot - A Modular IRC Bot For Win32
Copyright (C) 2005 [NSA] Team
This is private software, you must never redistribute this source code
Redistribution of binary forms, with or without modification,
are permitted provided that the following conditions are met:

  1. The name of the author may not be used to endorse or promote products
  derived from this software without specific prior written permission.
  2. The binary and source may not be sold and/or given away for free.
  3. You can only create binaries for your own usage, not for any
  third parties.
  4. The person using this sourcecode is a developer of said sourcecode.
  
	Redistribution and use in source forms, with or without modification,
	are not permitted.
	This license may be changed without prior notice.
		  
			THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
			IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
			OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
			IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
			INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
			NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
			DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
			THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
			(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
			THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/






#ifndef __DCOM_H__
#define __DCOM_H__

void Dcom(ExploitInfo_s* pExploitInfo);
void Dcom2(ExploitInfo_s* pExploitInfo);

char *CreateDCOMPacket(ExploitInfo_s pExploitInfo, DWORD *dwRequestSize, int iTargetOs, bool bNamedPipe);
inline int GenerateDCOMRequestPacket(ExploitInfo_s pExploitInfo, char szRequestBuffer[2048], int iTargetOS);

#endif // __DCOM_H__
