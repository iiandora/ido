//#define _CRT_SECURE_NO_WARNINGS

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


#include "iwstr.h"
#include "rtag.h"
//#include "json.hpp"

int g_cml = 0;

int getnlen(wstring& s)
{
	wstring st = wstrbt(s, wstring(L"-n["), wstring(L"]-"));
	return  _wtoi(st.c_str());
}


void dodir(wstring& cml, wstring& exedir, wstring& path)
{

	HANDLE hFind(NULL);
	WIN32_FIND_DATA fd;

	wstring sfilter = L"\\*.*";
	wstring sfind;

	//TCHAR szFind[2048];
	//lstrcpy(szFind, path);
	//lstrcat(szFind, _T("\\*.*"));

	__int64 lsz = 0;
	SYSTEMTIME stsys;
	FILETIME localftime;

	wchar_t ibuf[512];
	wchar_t timebuf[1024];
	wchar_t tbuf[1024];
	//wchar_t szFolder[2048];

	wchar_t dirbuf[64];

	long icount = 0;

	int isfind = 0;
	int isxn = 0;
	int isxa = 0;
	int isxx = 0;

	int isdt = 0;
	int isds = 0;
	int isbdt = 0;
	int isbds = 0;
	int isnlen = 0;
	int nlen = 0;
	int isatype = 0;
	int isxtype = 0;


	int issz = 0;
	int isdi = 0;

	int m_isbyym = 0;
	int	m_isbyy = 0;
	int m_islow = 0;



	int ismore = 0;
	int isdir = 0;
	int isdo = 0;
	int isall = 0;
	int isnew = 0;
	int isend = 0;
	int ismove = 0;
	int isdelstr = 0;
	int isdelchar = 0;
	int isrp = 0;
	int islog = 0;	

	int isks = 0;

	wstring sdel = L"";
	wstring sdelchar = L"";
	wstring rpa = L"";
	wstring rpb = L"";
	vector<std::wstring> vrp;


	wstring sfile;
	wstring sname;
	wstring stype;

	wstring sthis;
	wstring snew;

	vector<wstring> vecwtrl;
	wstring str;
	wstring sxan;
	wstring sdir;


	sfilter = path + sfilter;
	hFind = FindFirstFileW(sfilter.c_str(), &fd);


	if (hFind == INVALID_HANDLE_VALUE)
	{
		wprintf(L"\r\nerr:invalid %ls\r\n", sfilter.c_str());
		return;;
	}

	nlen = getnlen(cml);
	if (nlen > 0)
	{
		isnlen = 1;
	}

	if (wstrfind(cml, wstring(L".all")))
	{
		isall = 1;
	}

	if (wstrfind(cml, wstring(L"-f["))) {
		sfind = wstrbt(cml, wstring(L"-f["), wstring(L"]-"));
		isfind = 1;
	}

	if (wstrfind(cml, wstring(L" -log ")))
	{
		islog = 1;
	}

	if (wstrfind(cml, wstring(L" -more ")))
	{
		ismore = 1;
	}

	if (wstrfind(cml, wstring(L"-c["))) {
		isdelchar = 1;
		sdelchar = wstrbt(cml, wstring(L"-c["), wstring(L"]-"));
	}
	if (wstrfind(cml, wstring(L"-x["))) {
		isdelstr = 1;
		sdel = wstrbt(cml, wstring(L"-x["), wstring(L"]-"));
	}

	if (wstrfind(cml, wstring(L"-r["))) {
		wstring srp = L"";
		isrp = 0;
		srp = wstrbt(cml, wstring(L"-r["), wstring(L"]-"));
		wstrSplitData(srp, L"#", vrp);
		if (vrp.size() == 2) {
			isrp = 1;
			rpa = vrp[0];
			rpb = vrp[1];
			wprintf(L"%ls", rpa.c_str());
			wprintf(L"%ls", rpb.c_str());
		}
		else {
			isrp = 0;
			wprintf(L"\r\n-r[]- err\r\n");
		}
	}


	if (wstrfind(cml, wstring(L"-dir ")))
	{
		isdir = 1;
	}

	if (wstrfind(cml, wstring(L" -new ")))
	{
		isnew = 1;
	}
	if (wstrfind(cml, wstring(L" -do ")))
	{
		isdo = 1;
	}

	if (wstrfind(cml, wstring(L" -xn ")))
	{
		isxn = 1;
	}

	if (wstrfind(cml, wstring(L" -xa ")))
	{
		isxa = 1;
	}

	if (wstrfind(cml, wstring(L" -xx ")))
	{
		isxx = 1;
	}


	if (wstrfind(cml, wstring(L" -end ")))
	{
		isend = 1;
	}

	if (wstrfind(cml, wstring(L" -dt ")))
	{
		isdt = 1;
	}
	if (wstrfind(cml, wstring(L" -ds ")))
	{
		isds = 1;
		isdt = 0;
	}


	if (wstrfind(cml, wstring(L" -bdt ")))
	{
		isbdt = 1;
		isds = 0;
		isdt = 0;
	}
	if (wstrfind(cml, wstring(L" -bds ")))
	{
		isbds = 1;
		isbdt = 0;
		isds = 0;
		isdt = 0;
	}

	if (wstrfind(cml, wstring(L" -sz ")))
	{
		issz = 1;
	}

	if (wstrfind(cml, wstring(L" -di ")))
	{
		isdi = 1;
	}

	if (wstrfind(cml, wstring(L" -move ")))
	{
		ismove = 1;
	}

	if (wstrfind(cml, wstring(L" -xtype ")))
	{
		isxtype = 1;
	}

	if (wstrfind(cml, wstring(L" -atype ")))
	{
		isatype = 1;
		isxtype = 0;
	}

	if (wstrfind(cml, wstring(L" -ksid ")))
	{
		isks = 1;
	}

	if (wstrfind(cml, wstring(L" -byy ")))
	{
		m_isbyy = 1;
		ismove = 1;
	}
	if (wstrfind(cml, wstring(L" -bym ")))
	{
		m_isbyym = 1;
		ismove = 1;
	}
	if (wstrfind(cml, wstring(L" -low ")))
	{
		m_islow = 1;
	}

	while (1)
	{
		if (FindNextFile(hFind, &fd) == FALSE) { break; }

		if (_tcscmp(fd.cFileName, L".") == 0 || _tcscmp(fd.cFileName, L"..") == 0)
		{
			continue;
		}

		sfile = wstring(fd.cFileName);
		sthis = path + L"\\" + sfile;
		snew.clear();

		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (isdir) {
				snew = wdir(sfile);
				if (snew.length() < 2) {
					icount++;
					wmemset(ibuf, 0, sizeof(ibuf) / sizeof(wchar_t));
					swprintf(ibuf, 128, L"%04d", icount);
					if (snew.length() == 0)
					{
						snew = wstring(ibuf);
					}
					else {
						if (isend) {
							snew = snew + L"_" + wstring(ibuf);
						}
						else {
							snew = wstring(ibuf) + L"_" + snew;
						}
					}
				}

				wprintf(L"\r\n%ls->%ls", sfile.c_str(), snew.c_str());

				if (isdo) {
					snew = path + L"\\" + snew;
					logrn(sthis, snew);
				}
			}

			if (ismore) {
				//memset(szFolder, 0, sizeof(szFolder));
				//swprintf(szFolder, 1024, L"%ls\\%ls", path, fd.cFileName);				
				dodir(cml, exedir, sthis);
			}
			else {
				continue;
			}

		}
		else
		{
			sname.clear();
			stype.clear();
			vecwtrl.clear();
			sxan.clear();
			str.clear();

			sname = wgetFileName(sfile);
			stype = wgetFileType(sfile);


			if (wstrfind(sfile, wstring(L".exe")))
			{
				continue;
			}
			if (wstrfind(sfile, wstring(L"ok.txt")))
			{
				continue;
			}
			if (wstrfind(sfile, wstring(L"err.txt")))
			{
				continue;
			}


			if (isfind)
			{
				if (!wstrfind(sfile, sfind))
				{
					continue;
				}
			}


			if (stype.empty() || !wstrfind(cml, stype))
			{
				if (isall) {}
				else { continue; }
			}

			if (isks) {
				wstring suid;
				if (getksuid(sthis, suid))
				{
					wprintf(L"\r\n%ls ->%ls", sthis.c_str(), suid.c_str());
					if (!ismove)
					{
						suid = path + L"\\" + suid;
					}

					if (isdo)
					{
						logrn(sthis, suid);
					}
				}
				continue;

			}


			//wcout << endl;
			//DWORD ws;
			//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sfile.c_str(), sfile.length(), &ws, NULL);

			//wcout << endl << sfile;
			//wcout.clear();

			wprintf(L"\r\n%ls", sthis.c_str());
			if (islog)
			{
				if (isfind)
				{
					wlog(sfind.append(L"_f.txt"), sthis);
				}
				else {
					wlog(L"log", sthis, 1);
				}
			}

			if (isdt || isds || m_isbyy || m_isbyym) {

				FileTimeToLocalFileTime(&fd.ftLastWriteTime, &localftime);
				FileTimeToSystemTime(&localftime, &stsys);
			}

			if (isbdt || isbds) {

				FileTimeToLocalFileTime(&fd.ftCreationTime, &localftime);
				FileTimeToSystemTime(&localftime, &stsys);
			}

			if (isdt || isbdt)
			{
				memset(timebuf, 0, sizeof(timebuf));
				swprintf(timebuf, 512, L"%d%02d%02d-%02d%02d%02d", stsys.wYear, stsys.wMonth, stsys.wDay, stsys.wHour, stsys.wMinute, stsys.wSecond);
				vecwtrl.push_back(wstring(timebuf));

			}
			if (isds || isbds)
			{
				memset(timebuf, 0, sizeof(timebuf));
				swprintf(timebuf, 512, L"%d%02d%02d", stsys.wYear, stsys.wMonth, stsys.wDay);
				vecwtrl.push_back(wstring(timebuf));

			}
			if (issz)
			{
				lsz = (__int64)MAXDWORD + 1;
				lsz = fd.nFileSizeHigh * lsz + fd.nFileSizeLow;
				memset(tbuf, 0, sizeof(tbuf));
				swprintf(tbuf, 512, L"%06lld", lsz);
				vecwtrl.push_back(wstring(tbuf));

			}
			if (isdi)
			{
				icount++;
				memset(ibuf, 0, sizeof(ibuf));
				swprintf(ibuf, 512, L"%04d", icount);
				vecwtrl.push_back(wstring(ibuf));
			}
			if (m_isbyym)
			{
				memset(dirbuf, 0, sizeof(dirbuf));
				swprintf(dirbuf, 64, L"%d%02d", stsys.wYear, stsys.wMonth);

				sdir = wstring(dirbuf);
				wmkdir(sdir);
			}
			if (m_isbyy)
			{
				memset(dirbuf, 0, sizeof(dirbuf));
				swprintf(dirbuf, 64, L"%d", stsys.wYear);

				sdir = wstring(dirbuf);
				wmkdir(sdir);
			}




			if (isnew) {
				sxan = wstring(L"");
			}
			else {

				sxan = sname;
				if (isxa) {
					sxan = walnum(sname);
				}

				if (isxn) {
					sxan = walpha(sname);
				}

				if (isxx) {
					sxan = wdir(sname);
				}

				// do on sxan
				if (isdelstr)
				{
					sxan = wremovestr(sxan, sdel);
				}

				if (isdelchar)
				{
					sxan = wremovechar(sxan, sdelchar);

				}

				if (isrp)
				{
					wreplace(sxan, rpa, rpb);
				}

				if (isnlen)
				{
					int len = sxan.length();
					if (len > nlen)
					{
						sxan = sxan.substr(0, nlen);
					}
				}
				if (m_islow)
				{
					wstring _str = sxan;
					sxan = makelower(_str);

				}

			}


			size_t ivsz = vecwtrl.size();
			if (ivsz > 0)
			{
				str.clear();

				for (size_t i = 0; i < ivsz; i++)
				{
					str = str + vecwtrl[i] + L"_";
				}
				str.pop_back();

				vecwtrl.clear();
			}


			if (isend) {
				snew = sxan + str;
			}
			else {
				snew = str + sxan;
			}

			if (isatype) {
				wstring rtype = L"";
				if (readfiletype(sthis.c_str(), rtype))
				{
					stype = rtype;
				}
			}

			if (isxtype)
			{
				if (iscanrm(stype))
				{
					stype = L"";
				}
			}

			//default

			snew = snew + stype;

			if (ismove) {

			}
			else {
				snew = path + L"\\" + snew;
			}

			if (m_isbyy || m_isbyym)
			{
				snew = exedir + L"\\" + sdir + L"\\" + snew;
			}




			if (sthis != snew) {

				wprintf(L"\r\n->%ls", snew.c_str());

				if (isdo) {
					logrn(sthis, snew);

				}

			}

		}
	}

	FindClose(hFind);

}


void docml(wstring& cml)
{
	TCHAR dir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, dir);
	dodir(cml, wstring(dir), wstring(dir));
	SetCurrentDirectory(dir);
}

void getcml()
{
	int imode = 0;
	TCHAR buf[1024];
	wstring  cml = L"\r\n -----\r\n .all, -dir, -f[x]-, -log| -more ";
	cml.append(L"\r\n | -xn| -xa| -xx | -x[]-| -c[]-| -r[a#b]-| -n[]-| -low");
	cml.append(L"\r\n | -dt| -ds| -bdt| -bds | -sz  | -di  | -xtype | -atype");
	cml.append(L"\r\n | -new | -end | -move | -dir | -byy | -bym | -do");
	cml.append(L"\r\n | q exit\r\n---- - \r\n");

	do {
		wprintf(L"%ls", cml.c_str());
		memset(buf, 00, sizeof(buf));
		_getws_s(buf, 1024);
		if (buf[0] == L'q') {
			break;
		}
		else if (buf[0] == L'@') {
			redo(buf + 1);
		}
		else {
			g_cml = 0;
			docml(wstring(buf) + L" ");
			g_cml = 0;
		}
	} while (1);

}

void _tmain(int argc, TCHAR* argv[])
{
	//SetConsoleOutputCP(65001);
	/*
	wcout<<L"DDDD \u2612!\n";
	wcout << L'☒';
	*/
	//char *p = setlocale(LC_ALL, NULL);
	//printf("%s\n", p); //C  default


	//设置为简体中文，使用UTF-8编码
	//在 Windows 下可以写作 
	setlocale(LC_ALL, "");
	//setlocale(LC_ALL, "chs");

	 //在 Linux 
	//setlocale(LC_ALL, "");
	//setlocale(LC_ALL, "zh_CN.UTF-8");

	//在 Mac OS 下可以写作 
	//setlocale(LC_ALL, "zh_CN"); 
	//setlocale(LC_ALL, "zh_CN.UTF-8");

#ifdef _UNICODE
	locale::global(locale(""));//多字节不能显示,所以加了个开关
	wcout.imbue(locale(""));
#endif

	/*

CONSOLE_FONT_INFOEX cfi;
cfi.cbSize = sizeof cfi;
cfi.nFont = 0;
cfi.dwFontSize.X = 0;
cfi.dwFontSize.Y = 20;
cfi.FontFamily = FF_DONTCARE;
cfi.FontWeight = FW_NORMAL;
wcscpy_s(cfi.FaceName, L"Arial Unicode MS");
SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

*/

/*
	wstring  str = L" ____fs45 -l[)-1  hgjhgj 56  0[]-da我唉-[你fsdfd __fdsaf--aa__   ";
	wstring st = wstrbt(str, wstring(L"-l["), wstring(L"]-"));
	wcout << st << endl;

wcout << str << endl;
wstring  tws = trim_ws(str);
wcout << tws << endl << trim_ws_xhx(tws) << endl;
wreplace(tws, L" ", L"");
wcout << tws << endl;
wreplace(tws, L"a", L"啊");
wcout << tws << endl;
*/


	if (argc >= 2) {
		wstring cml = L"";
		for (int i = 1;i < argc;i++)
		{
			cml = cml + argv[i] + L" ";
		}
		//wcout << argc << L">" << cml << endl; 
		wprintf(L"%d %ls\r\n", argc, cml.c_str());
		docml(cml);
	}
	else {
		getcml();
	}
}

