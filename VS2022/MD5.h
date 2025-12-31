
#ifndef MD5_H
#define MD5_H

#if     _MSC_VER > 1000
#pragma once
#endif

#include <string>
#include <fstream>
 
/* Type define */
typedef unsigned char byte;
typedef unsigned int uint32;
 
using std::string;
using std::ifstream;
 
/* MD5 declaration. */
class CMD5 {
public:
	CMD5();
	CMD5(const void* input, size_t length);
	CMD5(const string& str);
	CMD5(ifstream& in);
	void update(const void* input, size_t length);
	void update(const string& str);
	void update(ifstream& in);
	const byte* digest();
	string toString();
	void reset();

	CHAR *GetFileMD5(const char * filename) ;
	CHAR *GetBytesMD5(BYTE *pszBytes,int nLen) ;
 
private:
	void update(const byte* input, size_t length);
	void final();
	void transform(const byte block[64]);
	void encode(const uint32* input, byte* output, size_t length);
	void decode(const byte* input, uint32* output, size_t length);
	string bytesToHexString(const byte* input, size_t length);
 
	/* class uncopyable */
	CMD5(const CMD5&);
	CMD5& operator=(const CMD5&);
 
private:
	uint32 _state[4];	/* state (ABCD) */
	uint32 _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
	byte _buffer[64];	/* input buffer */
	byte _digest[16];	/* message digest */
	bool _finished;		/* calculate finished ? */
 
	static const byte PADDING[64];	/* padding for calculate */
	static const char HEX[16];
	enum { BUFFER_SIZE = 1024 };
};

std::string GetStringMD5(const std::string&strString);
std::string GetDataMD5(const void *pData,DWORD dwLen);
std::string GetFileMD5(const std::string&strFile);


#endif