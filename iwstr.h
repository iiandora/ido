#pragma once
#include <windows.h>

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <direct.h>
#include <io.h>
#include <vector>

#include <tchar.h>
#include <wchar.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <iosfwd>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

std::string wcharToChar(const std::wstring& source)
{
	if (source.empty())
	{
		return std::string();
	}
	int length = WideCharToMultiByte(CP_UTF8, 0, &source[0], source.size(), NULL, 0, NULL, NULL);
	std::string str(length, 0);
	WideCharToMultiByte(CP_UTF8, 0, &source[0], source.size(), &str[0], length, NULL, NULL);
	return str;
}

std::wstring charToWchar(const std::string& source)
{
	if (source.empty())
	{
		return std::wstring();
	}
	int length = MultiByteToWideChar(CP_UTF8, 0, &source[0], source.size(), NULL, 0);
	std::wstring wstr(length, 0);
	MultiByteToWideChar(CP_UTF8, 0, &source[0], source.size(), &wstr[0], length);
	return wstr;
}



int w2int(wstring& a)
{
	return  _wtoi(a.c_str());
}

wstring makelower(const wstring& str)
{
	wstring ret(str);
	wstring::size_type i = 0;
	for (i = 0; i < ret.length(); i++)
		ret[i] = towlower(ret[i]);
	return ret;
}

wstring makeupper(const wstring& str)
{
	wstring ret(str);
	wstring::size_type i = 0;
	for (i = 0; i < ret.length(); i++)
		ret[i] = towupper(ret[i]);
	return ret;
}


bool wstrfind(wstring& iput, wstring& str)
{
	if (str.empty()) { return false; }
	wstring si = makelower(iput);
	wstring sf = makelower(str);
	if (si.find(sf) != wstring::npos) { return true; }
	return false;
}

wstring wstrbt(wstring src, wstring& s1, wstring& s2)
{
	wstring str = L"";
	size_t f1;
	size_t f2;
	int len1 = s1.length();
	int len2 = s2.length();
	f1 = src.find(s1);
	if (f1 != wstring::npos)
	{
		f2 = src.find(s2, f1 + len1);
		if (f2 != wstring::npos) {
			str = src.substr(f1 + len1, f2 - f1 - len1);
		}
	}
	return str;

}

wstring wremovestr(wstring s1, wstring s2)
{
	wstring str = s1;
	size_t found;
	if (!s2.empty()) {
		found = str.find(s2);
		while (found != wstring::npos)
		{
			str.erase(found, s2.length());
			found = str.find(s2);
		}
	}
	return str;
}


void wreplace(wstring& target, const wstring& find, const wstring& replace)
{
	const wstring::size_type find_len = find.length();
	const wstring::size_type replace_len = replace.length();
	wstring::size_type pos = 0;
	while ((pos = target.find(find, pos)) != wstring::npos)
	{
		target.replace(pos, find_len, replace);
		pos += replace_len;
	}
}

wstring wremovechar(wstring s1, wstring s2)
{
	wstring str = s1;
	size_t found;
	if (!s2.empty()) {
		found = str.find_first_of(s2);
		while (found != wstring::npos)
		{
			str.erase(found, 1);
			found = str.find_first_of(s2);
		}
	}
	return str;
}


static inline void wstrSplitData(const std::wstring& str, const std::wstring& delimiter, std::vector<std::wstring>& vec_data)
{
	std::wstring s = str + delimiter;
	size_t pos = 0;
	std::wstring token;
	while ((pos = s.find(delimiter)) != std::wstring::npos)
	{
		token = s.substr(0, pos);
		vec_data.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
}

static inline bool wFindCRLF(const std::wstring& s)
{
	if (s.find(L"\r\n") != std::wstring::npos)
		return true;
	else
		return false;
}

inline std::wstring wJoinListBySeparator(const std::vector<std::wstring>& vec, const std::wstring& separator)
{
	std::wstring str;
	for (unsigned int i = 0; i < vec.size(); ++i)
	{
		str = str + vec.at(i) + separator;
	}

	return str;
}




wstring trim_ws_begin(const wstring& str)
{
	if (str.empty())
		return str;

	wstring result(str);
	wstring::iterator it = result.begin();
	while (it != result.end() && _istspace(*it))
		++it;

	if (it != result.begin())
		result.erase(result.begin(), it);
	return result;
}

wstring trim_ws_end(const wstring& str)
{
	if (str.empty())
		return str;

	wstring result(str);
	wstring::reverse_iterator it = result.rbegin();
	while (it != result.rend() && _istspace(*it))
		++it;

	if (it != result.rbegin())
		result.erase(it.base(), result.end());
	return result;
}

wstring trim_ws(const wstring& str)
{
	if (str.empty())
		return str;

	wstring result(str);
	wstring::iterator it = result.begin();
	while (it != result.end() && _istspace(*it))
		++it;

	if (it != result.begin())
		result.erase(result.begin(), it);

	if (result.empty())
		return result;

	it = result.end() - 1;
	while (it != result.begin() && _istspace(*it))
		--it;

	if (it != result.end() - 1)
		result.erase(it + 1, result.end());
	return result;
}


wstring trim_ws_xhx(const wstring& str)
{
	if (str.empty())
		return str;

	wstring result(str);
	wstring::iterator it = result.begin();
	while (it != result.end() && (*it) == L'_')
		++it;

	if (it != result.begin())
		result.erase(result.begin(), it);

	if (result.empty())
		return result;

	it = result.end() - 1;
	while (it != result.begin() && (*it) == L'_')
		--it;

	if (it != result.end() - 1)
		result.erase(it + 1, result.end());
	return result;
}




wstring wgetFileName(wstring& s)
{
	size_t found;
	found = s.find_last_of(L".");
	if (found != wstring::npos)
	{
		return wstring(s.substr(0, found));
	}
	else {
		return wstring(s);
	}
}

wstring wgetFileType(wstring& s)
{
	size_t found;
	found = s.find_last_of(L".");
	if (found != wstring::npos)
	{
		wstring stp = s.substr(found);
		return stp;
	}
	else {
		return wstring(L"");
	}
}

wstring wdir(wstring& s)
{
	wstring sok = L"";
	int i = 0;
	int len = s.length();
	for (;i < len;i++)
	{
		if (s[i] >= 0X30 && s[i] <= 0X7A)
		{
			sok.push_back(s[i]);
		}
	}
	return sok;
}


wstring walnum(wstring& s)
{
	wstring sok = L"";
	int i = 0;
	int len = s.length();
	for (;i < len;i++)
	{
		//locale dep
		if (iswalnum(s[i]))
		{
			sok.push_back(s[i]);
		}
	}
	return sok;
}

wstring walpha(wstring& s)
{
	wstring sok = L"";
	int i = 0;
	int len = s.length();
	for (;i < len;i++)
	{
		//locale dep
		if (iswalpha(s[i]))
		{
			sok.push_back(s[i]);
		}
	}
	return sok;
}

void printBytes(const unsigned char* s, int len) {
	for (int i = 0; i < len; i++) {
		printf("0x%02x ", *(s + i));
	}
	printf("\n");
}




string ws2s(const wstring& ws)
{
	size_t i = 0;
	size_t len = ws.size() * 4 + 1;
	char* ds = new char[len];
	memset(ds, 0, len);

	setlocale(LC_ALL, "");
	wcstombs_s(&i, ds, len, ws.c_str(), len);
	setlocale(LC_ALL, "C");

	string result = ds;
	delete[]ds;
	return result;
}


std::wstring s2ws(const std::string& s)
{
	size_t   i = 0;
	size_t len = s.size() + 1;
	wchar_t* des = new wchar_t[len];
	wmemset(des, 0, len);

	setlocale(LC_ALL, "");
	mbstowcs_s(&i, des, len, s.c_str(), len);
	setlocale(LC_ALL, "C");

	std::wstring result = des;
	delete[]des;
	return result;
}


const std::string iws2s(const std::wstring& ws)
{
	size_t   i = 0;
	std::locale old_loc = std::locale::global(std::locale(""));
	const wchar_t* src_wstr = ws.c_str();
	size_t buffer_size = ws.size() * 4 + 1;
	char* dst_str = new char[buffer_size];
	memset(dst_str, 0, buffer_size);
	wcstombs_s(&i, dst_str, buffer_size, src_wstr, buffer_size);
	std::string result = dst_str;
	delete[]dst_str;
	std::locale::global(old_loc);
	return result;
}

const std::wstring is2ws(const std::string& s)
{
	size_t   i = 0;
	std::locale old_loc = std::locale::global(std::locale(""));
	const char* src_str = s.c_str();
	const size_t buffer_size = s.size() + 1;
	wchar_t* dst_wstr = new wchar_t[buffer_size];
	wmemset(dst_wstr, 0, buffer_size);
	mbstowcs_s(&i, dst_wstr, buffer_size, src_str, buffer_size);
	std::wstring result = dst_wstr;
	delete[]dst_wstr;
	std::locale::global(old_loc);
	return result;
}

wstring wgettime(int iwhat = 0)
{
	wchar_t buf[256];
	wstring stime;
	time_t t = time(NULL);
	struct tm tloc;
	localtime_s(&tloc, &t);
	memset(buf, 0, sizeof(buf));
	wsprintf(buf, L"%d%02d%02d", (1900 + tloc.tm_year), (1 + tloc.tm_mon), tloc.tm_mday);
	stime = buf;

	if (1 == iwhat) {
		memset(buf, 0, sizeof(buf));
		wsprintf(buf, L"_%02d%02d%02d", tloc.tm_hour, tloc.tm_min, tloc.tm_sec);
		stime = stime + buf;
	}
	return stime;
}

void wlog(wstring sf, wstring str, int atime = 0)
{
	FILE* fp = NULL;
	errno_t err;
	long fsz = 0;
	//x86 little endian =unsinged char [ff][fe]
	WORD wbom = 0xFEFF;
	wchar_t rn[] = L"\r\n";
	wstring sfile = sf;
	wstring stime;

	if (atime > 0)
	{
		stime = wgettime(0);
	}

	if (1 == atime)
	{
		sfile = stime + sfile;
	}

	err = _wfopen_s(&fp, sfile.c_str(), L"ab+");

	if (err == 0 && fp) {

		fseek(fp, 0L, SEEK_END);
		fsz = ftell(fp);
		if (fsz == 0) {
			fwrite(&wbom, 2, 1, fp);
		}

		if (2 == atime)
		{
			fwrite(stime.c_str(), sizeof(wchar_t), stime.length(), fp);
			fwrite(rn, sizeof(wchar_t), 2, fp);
		}
		if (3 == atime)
		{
			stime = wgettime(1);
			fwrite(stime.c_str(), sizeof(wchar_t), stime.length(), fp);

		}

		fwrite(str.c_str(), sizeof(wchar_t), str.length(), fp);

		// r 0d ,n 0a
		//fputwc(0x0D, fp);
		//fputwc(0x0A, fp);
		fwrite(rn, sizeof(wchar_t), 2, fp);

		fclose(fp);
	}
}


void logrn(wstring& s, wstring& des)
{
	int irn = _trename(s.c_str(), des.c_str());
	if (irn != 0)
	{
		wchar_t buf[1024];
		_tcserror_s(buf, 1024, errno);
		wlog(L"err.txt", wstring(buf) + L"\r\n" + s + L"*" + des);
	}
	else {
		wlog(L"ok.txt", s + L"*" + des);
	}
}


void rdolog(wstring& s, wstring& des)
{
	int irn = _trename(s.c_str(), des.c_str());
	if (irn != 0)
	{
		wchar_t buf[1024];
		_tcserror_s(buf, 1024, errno);
		wlog(L"rerr.txt", wstring(buf) + L"\r\n" + s + L"*" + des);
	}
	else {
		wlog(L"rok.txt", s + L"*" + des);
	}
}




int redo(wchar_t* fname)
{
	int ret = -1;
	wstring str;
	wchar_t buf[2048];
	FILE* fp = NULL;
	errno_t err;

	//long fsz = 0;
	//int i = 0;

	wchar_t* p = NULL;

	wstring s1;
	wstring s2;
	size_t f1;

	err = _wfopen_s(&fp, fname, L"rb");
	if (fp == NULL) {
		//wcout << L"Error opening file" << endl;
		wprintf(L"Error opening file\r\n");
	}
	else {
		if (0 == err) {
			fseek(fp, 2, SEEK_SET); //bom FFFE

			//fseek(fp, 0L, SEEK_END);
			//fsz = ftell(fp);
			do
			{
				//i++;
				str = L"";
				memset(buf, 0, sizeof(buf));
				p = fgetws(buf, sizeof(buf) / sizeof(buf[0]), fp);

				str = buf;
				//wcout << buf << endl << str.length() << endl; // end \r\n =13,10

				if (str.size() > 3)
				{
					str.pop_back();
					str.pop_back();
					f1 = str.find(L"*");
					if (f1 != string::npos)
					{
						s1 = str.substr(0, f1);
						s2 = str.substr(f1 + 1);
						//wcout << endl<<s2 << L"->"<<s1;
						//wcout.clear();
						wprintf(L"\r\n%ls->%ls", s2.c_str(), s1.c_str());

						rdolog(s2, s1);
					}
				}

			} while (NULL != p);

			fclose(fp);
			ret = 1;
		}
	}
	return ret;
}

int wmkdir(wstring dir)
{
	//io.h
	int ret = _taccess(dir.c_str(), 0);
	if (0 != ret)
	{
		//wchar_t buf[1024];
		//_tcserror_s(buf, 1024, errno);	
		//wlog(L"errmkdir.txt", wstring(buf) + L"\r\n" + dir);			
		//_mkdir  0 ok ,-1 err	
		ret = _tmkdir(dir.c_str());
		if (0 == ret) {
			wlog(L"okmkdir.txt", dir);
		}
	}
	return ret+1;
}