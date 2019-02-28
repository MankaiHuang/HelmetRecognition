#include "StdAfx.h"
#include "Utils.h"

// ����ת��ʹ��
#include <atlconv.h>

// �����ֽ�ת���ɶ��ֽ�
CStringA CUtils::WChar2MByte(const CString &str)   
{ 
    // ����nCharLen��nByteLen��ֵ��С��ͬ, nCharLen�ǰ��ַ�����ģ�nByteLen�ǰ��ֽڼ����
    int nCharLen = str.GetLength();
    // ��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����
    int nByteLen = WideCharToMultiByte(CP_UTF8, 0, str, nCharLen, NULL, 0, NULL, NULL);
    
    //Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ŀ��ֽ��ֽڴ�С
    char* pStr = (char*)malloc(sizeof(char)*(nByteLen+1)); // ���ֽ�Ϊ��λ

    //���ֽڱ���ת���ɶ��ֽڱ���
    WideCharToMultiByte(CP_UTF8, 0, str, nCharLen, pStr, nByteLen, NULL, NULL);
    pStr[nByteLen] = '\0';   //���ֽ��ַ���'\0'����
    
    // ת����CStringA����
    CStringA strA(pStr);

    // ɾ����ʱ����
    free(pStr);

    return strA;
}

void CUtils::WChar2Char( char *dst, CString &src, int size)
{
	// ����nCharLen��nByteLen��ֵ��С��ͬ, nCharLen�ǰ��ַ�����ģ�nByteLen�ǰ��ֽڼ����
	int nCharLen = src.GetLength();
	// ��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����
	int nByteLen = WideCharToMultiByte(CP_UTF8, 0, src, nCharLen, NULL, 0, NULL, NULL);

	if(nByteLen > size)
	{
		return;
	}

	//���ֽڱ���ת���ɶ��ֽڱ���
	WideCharToMultiByte(CP_UTF8, 0, src, nCharLen, dst, nByteLen, NULL, NULL);
	dst[nByteLen] = '\0';   //���ֽ��ַ���'\0'����
}

// �����ֽ�ת���ɿ��ֽ�
CString CUtils::MByte2WChar(const CStringA &strA)
{
    // �����ֽ��������ֽ�Ϊ��λ��һ������ռ�����ֽ�
    int charLen = strA.GetLength();

    // ������ֽ��ַ��Ĵ�С�����ַ����㡣
    int nByteLen = MultiByteToWideChar(CP_UTF8, 0, strA, charLen, NULL, 0);
    wchar_t* pStr = (wchar_t*)malloc(sizeof(wchar_t)*(nByteLen+1));
    MultiByteToWideChar(CP_UTF8, 0, strA, charLen, pStr, nByteLen);
    pStr[nByteLen] = '\0';
    CString str(pStr);
    free(pStr);

    return str;
}

CString CUtils::Char2Str(char* pstr)
{
    // �����ֽ��������ֽ�Ϊ��λ��һ������ռ�����ֽ�
    int charLen = strlen(pstr);
    // ������ֽ��ַ��Ĵ�С�����ַ����㡣
    int nByteLen = MultiByteToWideChar(CP_UTF8, 0, pstr, charLen, NULL, 0);
    wchar_t* pszWchar = (wchar_t*)malloc(sizeof(wchar_t)*(nByteLen+1));
    MultiByteToWideChar(CP_UTF8, 0, pstr, charLen, pszWchar, nByteLen);
    pszWchar[nByteLen] = '\0';
    CString str(pszWchar);
    free(pszWchar);

    return str;
}

string CUtils::Str2Stda(CString &strDim)
{
    CStringA stra(strDim.GetBuffer(0));
    strDim.ReleaseBuffer();

    string str;
    str = stra.GetBuffer(0);
    stra.ReleaseBuffer();

    return str;
}

// ��unicode����ת��utf8
CStringA CUtils::UniToUtf8(const CString &str)
{
    int len;
    len = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
    char *pszUtf8 = (char*)malloc(len + 1);
    memset(pszUtf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, str, -1, pszUtf8, len, NULL, NULL);

    // ת����CStringA����
    CStringA strA(pszUtf8);
    free(pszUtf8);
    return strA;
}
