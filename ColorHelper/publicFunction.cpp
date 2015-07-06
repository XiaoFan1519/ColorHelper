#include "stdafx.h"
#include "publicFunction.h"

//��һ��ʮ�������ַ�����ʽ����7���ַ���ʾ 
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

//��COLORREFת����16�����ַ���
void getColorHex(COLORREF color, wchar_t* buf) {
	int colorNum = 0, R, G, B;
	R = (color & 0xff) << 16;
	G = color & 0xff00;
	B = (color & 0xff0000) >> 16;
	colorNum = R | G | B;
	_itow(colorNum, buf, 16);
	makeHex(buf);
}

//��120px�����ַ���ת��������
int styleToInt(const wchar_t *strVal) {
	//���Ҫ���ص�ֵ
	int value = 0;
	//ȥ�������px
	int strLen = wcslen(strVal) - 2;
	//�����ȡ����ַ���
	wchar_t tmp[255];
	wcscpy_s(tmp, 255, strVal);
	//���ý�����
	tmp[strLen] = '\0';
	value = _wtoi(tmp);
	return value;
}

//��ָ����С�����ص�
void drawPixel(HDC hdc, int x, int y, COLORREF color, int multiple) {
	int startX = x * multiple;
	int startY = y * multiple;
	for (int i = 0; i < multiple; i++)
	{
		for (int j = 0; j < multiple; j++)
		{
			SetPixel(hdc, startX + j, startY + i, color);
		}
	}
}