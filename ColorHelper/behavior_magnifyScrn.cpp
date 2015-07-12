#include "stdafx.h"
#include "behavior_manifyScrn.h"
namespace htmlayout {
	//�Զ����behavior�������������λ�õ�ͼ��
	//Ԫ�����ԣ�
	//isupdate�� true��ʾ����Ԫ�ص�ͼ��Ϊ��ǰ���λ�õ�ͼ��false��ʹ�û����е�ͼ��
	//multiple�� ��ͼ��Ŵ�ı���

	magnifyScrn::magnifyScrn() : behavior(HANDLE_ALL, "magnifyScrn") {

	}

	magnifyScrn::~magnifyScrn() {
		DeleteObject(hBitMap);
	}

	void magnifyScrn::attached(HELEMENT he)
	{
		dom::element el = he;
		//��ȡԪ�صĴ�С
		elementWidht = styleToInt(el.get_style_attribute("width"));
		elementHeight = styleToInt(el.get_style_attribute("height"));
		//��÷Ŵ���
		multiple = _wtoi(el.get_attribute("multiple"));
		//�Ŵ�ǰ��ͼ���С
		width = ceil((float)elementWidht / multiple);
		height = ceil((float)elementHeight / multiple);
	}

	void magnifyScrn::detached(HELEMENT he)
	{

	}

	BOOL magnifyScrn::on_draw(HELEMENT he, UINT draw_type, HDC hdc, const RECT& rc) {
		
		dom::element el = he;
		std::wstring str = el.get_attribute("isupdate");
		
		if (L"false" == str){
			dc.printf("ʹ�û��滭��");
			HDC cdc = CreateCompatibleDC(hdc);
			HGDIOBJ oldBitmap = SelectObject(cdc, hBitMap);
			// +1 ����Ϊ�߿��ԭ��
			BitBlt(hdc, rc.left + 1, rc.top + 1, elementWidht - 1, elementHeight - 1, cdc, 0, 0, SRCCOPY);
			SelectObject(cdc, oldBitmap);
			DeleteDC(cdc);
			return false;
		}

		//��÷ֱ���
		int ScrWidth = GetDeviceCaps(hdc, HORZRES);
		int ScrHeight = GetDeviceCaps(hdc, VERTRES);
		//������Ļ��DC�����ڻ�ȡͼ��
		HDC fullDC = GetDC(nullptr);
		HBITMAP fullBitMap = CreateCompatibleBitmap(fullDC, ScrWidth, ScrHeight);
		HDC fullcdc = CreateCompatibleDC(fullDC);
		HGDIOBJ oldFullBitmap = SelectObject(fullcdc, fullBitMap);
		//��������Ļ��DC���Ƶ�����DC��
		BitBlt(fullcdc, 0, 0, ScrWidth, ScrHeight, fullDC, 0, 0, SRCCOPY);
		//Ԫ�صļ���DC
		if (false == iscreate) {
			hBitMap = CreateCompatibleBitmap(hdc, elementWidht + 20, elementHeight + 20);
		}
		HDC cdc = CreateCompatibleDC(hdc);
		HGDIOBJ oldBitmap = SelectObject(cdc, hBitMap);
		//������λ��
		POINT pt;
		GetCursorPos(&pt);
		//�洢Ҫȡ��ͼ��ķ�Χ
		RECT rect;
		rect.left = pt.x - (width / 2);
		rect.top = pt.y - (height / 2);
		rect.right = pt.x + (width / 2);
		rect.bottom = pt.y + (height / 2);

		//��ȫ����DC�������ڴ����ٽ���GetPixel�����߻����������
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				COLORREF color = GetPixel(fullcdc, rect.left + j, rect.top + i);
				drawPixel(cdc, j, i, color, multiple, elementWidht, elementHeight);
			}
		}

		// +1 ����Ϊ�߿��ԭ��
		BitBlt(hdc, rc.left + 1, rc.top + 1, elementWidht - 1, elementHeight - 1, cdc, 0, 0, SRCCOPY);

		//�ͷ�ȫ���ļ���DC
		SelectObject(fullcdc, oldFullBitmap);
		DeleteDC(fullcdc);
		DeleteObject(fullBitMap);
		ReleaseDC(nullptr, fullDC);
		//�ͷų���ļ���DC
		SelectObject(cdc, oldBitmap);
		DeleteDC(cdc);
		return false;
	}

	BOOL magnifyScrn::on_mouse(HELEMENT he, HELEMENT target, UINT event_type, POINT pt, UINT mouseButtons, UINT keyboardStates) {
		return false;
	}

	magnifyScrn magnifyScrn_instance;
}