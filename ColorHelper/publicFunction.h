#pragma once
#include "stdafx.h"

// ���ú���
//��COLORREFת����16�����ַ���
void getColorHex(COLORREF color, wchar_t* buf);
//��һ��ʮ�������ַ�����ʽ����7���ַ���ʾ 
void makeHex(wchar_t* buf);
//��120px�����ַ���ת��������
int styleToInt(const wchar_t *);
//��ָ����С�����ص�
void drawPixel(HDC hdc, int x, int y, COLORREF color, int multiple, int maxWidth, int maxHeight);