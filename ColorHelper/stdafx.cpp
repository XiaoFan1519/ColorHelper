// stdafx.cpp : source file that includes just the standard includes
// ColorHelper.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

//��һ��ʮ�������ַ�����ʽ����6���ַ���ʾ 
// #FFFFFF
void makeHex(wchar_t* buf) {
	// �6���ַ�
	int len = wcsnlen(buf, 6);
	// �ַ�������
	buf[7] = '\0';
	//���ַ�������
	for (int i = 6, j = len - 1; i >= 0; i--) {
		if (j >= 0)
		{
			buf[i] = buf[j];
			j--;
		}
		else if (i != 0) {
			//������Ĳ��ֲ�0
			buf[i] = '0';
		}
		else if (i == 0) {
			//��ͷ��#
			buf[i] = '#';
		}
	}
}

void getColorHex(COLORREF color, wchar_t* buf) {
	int colorNum=0, R, G, B;
	R = (color & 0xff) << 16;
	G = color & 0xff00;
	B = (color & 0xff0000) >> 16;
	colorNum = R | G | B;
	_itow(colorNum, buf, 16);
	makeHex(buf);
}