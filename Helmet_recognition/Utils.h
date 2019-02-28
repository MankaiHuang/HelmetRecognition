#pragma once
#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////////
// ������
class CUtils
{
public:
	// �����ֽ�ת���ɶ��ֽ�
    static CStringA WChar2MByte(const CString &str);
    // �����ֽ�ת���ɿ��ֽ�
    static CString MByte2WChar(const CStringA &strA);
	// �����ֽ�ת�����ַ�����
	static void WChar2Char(char *dst, CString &src, int size);

    // ��unicode����ת��utf8
    static CStringA UniToUtf8(const CString &str);
    // ��char����ת����CString
    static CString Char2Str(char* pstr);
    // ��CStringת����std::string
    static string Str2Stda(CString &strDim);
};