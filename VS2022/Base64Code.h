#ifndef __BASE64CODE_H__
#define __BASE64CODE_H__
extern "C"
{
int Base64Encode(const BYTE *pIn, int nInLen, BYTE **pOut);
int Base64Decode(const BYTE *pIn, int nInLen, BYTE **pOut);

void  ReveredBuffer(BYTE *pIn,int nInLen) ;
DWORD EncryptBuffer(const BYTE *pIn, BYTE **pOut,int nEncryptCount);
DWORD DecryptBuffer(const BYTE *pIn, BYTE **pOut);
}
#endif