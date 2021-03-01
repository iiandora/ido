#pragma once
#include "iwstr.h"

struct tagblock
{
	int len;
	unsigned char* hex;
	wchar_t* type;
};

unsigned char jpg[] = { 0xFF,0xD8,0xFF };
//unsigned char jpg[] = { 0xFF,0xD8,0xFF,0xE0 };
//unsigned char psjpg[] = { 0xFF,0xD8,0xFF,0xE2 };

unsigned char png[] = { 0x89,0x50,0x4E,0x47 };
unsigned char gif[] = { 0x47,0x49,0x46,0x38 };
unsigned char tif[] = { 0x49,0x49,0x2A,0x00 };
unsigned char bmp[] = { 0x42,0x4D };

unsigned char mp4begin[] = { 0x00,0x00,0x00 };

//[ 8 ]"ftypisom"	
unsigned char mp4str[] = { /**/0x66,0x74,0x79,0x70,0x33,0x67,0x70,0x35 };

unsigned char mkvbegin[] = { 0x1A,0x45,0xDF,0xA3 };
//[id ,size ,data]
//[ 8 ]"matroska"
unsigned char mkvstr[] = { 0x42,0x82,0x88,/**/0x6D,0x61,0x74,0x72,0x6F,0x73,0x6B,0x61 };



unsigned char avibegin[] = { 0x52,0x49,0x46,0x46 };
unsigned char avistr[] = { 0x41,0x56,0x49,0x20 };
unsigned char rm[] = { 0x2E,0x52,0x4D,0x46 };
unsigned char mpeg1[] = { 0x00,0x00,0x01,0xBA };
unsigned char mpeg2[] = { 0x00,0x00,0x01,0xB3 };
unsigned char mov[] = { 0x6D,0x6F,0x6F,0x76 };
unsigned char mov2[] = { 0x6D,0x64,0x61,0x74 };
unsigned char wmv[] = { 0x30,0x26,0xB2 };
unsigned char flv[] = { 0x46,0x4C,0x56,0x01 };
unsigned char zip[] = { 0x50,0x4B,0x03,0x04 };
unsigned char rar[] = { 0x52,0x61,0x72 };
unsigned char z7[] = { 0x37,0x7A,0xBC };

tagblock tag_mhd[] =
{
	{ 3, jpg,L".jpg" } ,
	{ 4, png,L".png" } ,
	{ 4, gif,L".gif" } ,
	{ 4, png,L".png" } ,
	{ 2, bmp,L".bmp" } ,
	{ 4,mkvbegin,L".mkv"},
	{ 4, mov,L".mov" } ,
	{ 3, wmv,L".wmv" } ,
	{ 3, flv,L".flv" } ,
	{ 4, avibegin,L".avi" } ,
	{ 4, mpeg1,L".mpeg" } ,
	{ 4, mpeg2,L".mpeg" } ,
	{ 3, rar,L".rar" } ,
	{ 4, zip,L".zip" } ,
	{ 3, z7,L".7z" } ,

	{ 0, NULL,NULL }
};

bool iscanrm(wstring& s)
{
	wstring str = L".bmp.jpg.jpeg.png.gif.mov.mp4.flv.mkv.wmv.avi.zip.rar";
	wstring sf = makelower(s);
	if (str.find(sf) != wstring::npos) { return true; }
	return false;
}


int readfiletype(const wchar_t* pfile, wstring& stype)
{

	size_t fsize = 0;
	size_t rsize = 0;
	errno_t err;
	int iok = 0;
	FILE* fp = NULL;
	unsigned char buf[1024];

	err = _wfopen_s(&fp, pfile, L"rb");
	if (0 != err)
	{
		return iok;
	}

	if (fp)
	{
		fseek(fp, 0L, SEEK_END);
		fsize = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		if (fsize < 128)
		{
			fclose(fp);
			return 0;
		}

		memset(buf, 0, sizeof(buf));
		rsize = fread(buf, 1, 32, fp);
		fclose(fp);

		if (memcmp(buf + 4, "ftyp", 4) == 0)
		{
			iok = 1;
			stype = L".mp4";
			return iok;
		}

		for (int i = 0;;i++) {
			if (0 == tag_mhd[i].len)
			{
				break;
			}
			if (memcmp(buf, tag_mhd[i].hex, tag_mhd[i].len) == 0)
			{
				iok = 1;
				stype = tag_mhd[i].type;
				break;
			}
		}


	}

	return iok;
}


uint32_t byte4i(unsigned char* p)
{
	uint32_t x = 0;
	unsigned char* tp = p;
	x = tp[0];
	x <<= 8;
	x |= tp[1];
	x <<= 8;
	x |= tp[2];
	x <<= 8;
	x |= tp[3];
	return  x;
}


int findBytes(unsigned char* buf, int blen, int istart, char* findstr, int dlen)
{
	unsigned char* p = buf;
	unsigned char* tp = p + istart;
	int ic = blen - istart - dlen;

	for (int i = 0; i < ic; i++) {
		if (tp[i] == findstr[0] && memcmp(tp + i, findstr, dlen) == 0)
		{
			return i + istart;
		}
	}
	return -1;
}

int finduid(unsigned char* buf, int blen, char* uid, int ulen)
{
	unsigned char* p1 = buf;
	unsigned char* p2 = buf;
	char px1[8] = "[uid:";
	char px2[8] = "]";
	int s = findBytes(buf, blen, 0, px1, 5);
	if (s < 0) { return 0; }

	p1 = p1 + s + 5;
	p2 = p1;
	int ic = blen - s;
	for (int i = 0; i < ic; i++)
	{
		p2++;
		if (*p2 == px2[0])
		{
			memcpy(uid, p1, p2 - p1);
			return 1;
		}
	}
	return 0;
}

int findGifshowU(unsigned char* buf, int blen, char* uid, int ulen)
{
	unsigned char* p1 = buf;
	unsigned char* p2 = buf;
	char px1[32] = "GIFSHOW [";
	char px2[8] = "]";
	int s = findBytes(buf, blen, 0, px1, 5);
	if (s < 0) { return 0; }

	p1 = p1 + s + 9;
	p2 = p1;
	int ic = blen - s;
	for (int i = 0; i < ic; i++)
	{
		p2++;
		if (*p2 == px2[0])
		{
			memcpy(uid, p1, p2 - p1);
			return 1;
		}
	}
	return 0;
}



int  getksuid(wstring& sfile, wstring& sid)
{

	int iok = 0;

	size_t fsize = 0;

	size_t rsize = 0;

	uint32_t tlen = 0;
	unsigned char buf[1024];
	unsigned char* tbuf = NULL;

	char uid[128];
	char ufile[256];

	errno_t err;
	FILE* fp = NULL;

	err = _wfopen_s(&fp, sfile.c_str(), L"rb");
	if (0 != err)
	{
		return 0;
	}

	fseek(fp, 0L, SEEK_END);

#if defined _WIN64
	fsize = _ftelli64(fp);
#else
	fsize = ftell(fp);
#endif

	fseek(fp, 0L, SEEK_SET);

	/*
	check if mp4
	4          4
	[ftpy-size]["ftpy"]

	*/
	if (fsize < 512)
	{
		return 0;
	}

	memset(buf, 0, sizeof(buf));
	rsize = fread(buf, 1, 8, fp);

	if (0 != memcmp(buf + 4, "ftyp", 4))
	{
		return 0;
	}

	//ok mp4
	tlen = byte4i(buf);

	//seek to "moov"
	int imoov = tlen - 8;
	fseek(fp, imoov, SEEK_CUR);

	rsize = fread(buf, 1, 8, fp);
	if (0 == memcmp(buf + 4, "moov", 4))
	{

		tlen = byte4i(buf);

		//read all moov
		tlen = tlen - 8;
		uint32_t xlen = tlen + 1;
		tbuf = new unsigned char[xlen];

		if (NULL != tbuf)
		{
			rsize = fread(tbuf, 1, tlen, fp);

			if (rsize == tlen)
			{
				//find udta   uis
				memset(uid, 0, sizeof(uid));
				if (finduid(tbuf, rsize, uid, 64)) { iok = 1; }
				else if (findGifshowU(tbuf, rsize, uid, 64)) { iok = 1; };
			}

			delete[] tbuf;
			tbuf = NULL;
		}
	}


	fclose(fp);

	memset(ufile, 0, sizeof(ufile));

	if (iok) {
		//%zd for size  ,%lld for long long int
		sprintf_s(ufile, "%s-%zd.mp4", uid, fsize);
	}
	else {

		sprintf_s(ufile, "t%zd.mp4", fsize);
	}
	sid = charToWchar(string(ufile));


	return 1;
}

